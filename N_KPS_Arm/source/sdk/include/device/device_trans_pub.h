
#ifndef _DEVICE_TRANS_PUB_NEW_H_
#define _DEVICE_TRANS_PUB_NEW_H_

class device_trans_pub
{
public:

	device_trans_pub();
	~device_trans_pub();
	
	bool s_update_laser( const SLaser& laser );
	bool s_update_odom( const SOdomSpeed& new_odom );
	bool s_call_back_amcl( const SPos &amcl_pos );
	bool s_call_back_particle(const SparticlePub &pub);
	bool s_call_back_reflector(const SReflector &ref);
	bool s_call_back_ref_pos(const SPOS_CONFIDENCE &confidence_pos);
	bool s_call_back_dyloc_pos(const SPOS_CONFIDENCE &confidence_pos);
	bool s_call_back_laser_ex( const SLaser_Ex& laser_ex );
	bool s_call_back_laser_ex_ref( const SLaser_Ex_Ref& laser_ex_ref );
	bool s_call_back_laser_ex_cab( const SLaserXYEx& laser_ex_cab );
	bool s_call_back_amcl_confidence( const SAMCL_CONFIDENCE &amcl_confidence );
	bool s_call_back_dynamic_pos( const SPOS_CONFIDENCE &confidence_pos );
	bool init_pos(const SInit_Pos &init_pos);
	bool set_map_cmd(const SCmd &set_map_cmd);

protected:
private:

	

};




#endif //_DEVICE_TRANS_PUB_NEW_H_
