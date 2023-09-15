
#ifndef DESCRIPTOR_H_
#define DESCRIPTOR_H_

#ifndef Q_MOC_RUN 
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/export.hpp>
#endif

class InterestPoint;
class LaserReading;
class OrientedPoint2D;

/**
 * Representation of an abstract descriptor.
 * The class represents an abstract descriptor, defining the interface for comparing two descriptors.
 *
 * @author Gian Diego Tipaldi
 */

class Descriptor {
	public:
		/** Clone function for prototyping. It implements the Prototype pattern. */
		virtual Descriptor* clone() const = 0;

		/** Default destructor. */
		virtual ~Descriptor() { }
		
		/** 
		 * Abstract interface for computing the distance between two descriptors. 
		 * The implementation of the actual distance is left to the inherited classes. 
		 * 
		 */
		virtual double distance(const Descriptor* descriptor) const = 0;
	
		/** 
		 * Returns the descriptor in the form of onedimensional histogram. The resulting vector represents the feature descriptor.
		 *
		 */
		virtual void getFlatDescription(std::vector<double>& description) const = 0;
	
		/** 
		 * Returns the descriptor in the form of a weighted onedimensional histogram. The resulting vectors represent the feature descriptor and the importance of each dimension.
		 * @param description the descriptor vector
		 * @param weight the descriptor variance
		 *
		 */
		virtual void getWeightedFlatDescription(std::vector<double>& description, std::vector<double>& weight) const
	    {getFlatDescription(description); weight.resize(description.size(),1.);}
   
    protected:
		friend class boost::serialization::access;
	
		/** Serializes the class using boost::serialization. */ 
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version);
};
#ifndef Q_MOC_RUN
template<class Archive>
void Descriptor::serialize(Archive& ar, const unsigned int version)
{
    BOOST_SERIALIZATION_ASSUME_ABSTRACT(Descriptor);
}
#endif

#if BOOST_VERSION > 104000
BOOST_CLASS_EXPORT_KEY(Descriptor);
#endif

/**
 * Representation of an abstract descriptor generator.
 * The class represents an abstract descriptor generator, defining the interface for generating the description of an interest point.
 *
 * @author Gian Diego Tipaldi
 */

class DescriptorGenerator{
    public:

		/** Default destructor. */
		virtual ~DescriptorGenerator() { }

		/** Abstract interface for generating a descriptors given an interest point and a laser reading. */
		virtual Descriptor* describe(const InterestPoint& _point, const LaserReading& reading) = 0;
		
		/** Abstract interface for generating a descriptors given a general point in \f$ \mathcal{SO}(2) \f$  and a laser reading. */
		virtual Descriptor* describe(const OrientedPoint2D& _point, const LaserReading& reading) = 0;
};

#endif

