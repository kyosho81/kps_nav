#include "math.h"
#include "Acc.h"


double Acc::CalAcc(double dt,double current,double acc,double dec,double set){

	double t_acc = fabs(acc*dt);
	double t_dec = fabs(dec*dt);

	if ( (set * current) < 0)
	{//diff speed dir, use dec

		//current negative speed
		if( current < 0 ){
			if ( (current + t_dec) < set)
			{
				set = current + t_dec;
				return set;
			}else{
				return set;
			}

		}else{//positive speed

			if ( ( current - t_dec) > set)
			{
				set = current - t_dec;
				return set;
			}else{
				return set;
			}
		}

	}else{// same speed dir

		//if increase
		if(fabs(set) > fabs(current)){

			//current negative speed increase
			if( (current < 0 ) || ( set < 0 )){

				if( (current - t_acc) > set ){
					set = current - t_acc;
					return set;
				}else{
					return set;
				}

			}else{//positive speed increase

				if( ( current + t_acc ) < set ){
					set = current + t_acc;
					return set;
				}else{

					return set;
				}
			}
		}//decrease
		else{
			//current negative speed decrease
			if( (current < 0 ) || ( set < 0 )){
				if( ( current + t_dec ) < set ){
					set = current + t_dec;
					return set;
				}else{
					return set;
				}
			}else{//positive speed decrease
				if( ( current - t_dec ) > set ){
					set = current - t_dec;
					return set;
				}else{
					return set;
				}
			}
		}


	}

	return set;

}

double Acc::CalAcc2(double current,double acc,double dec,double set){

	double t_acc = fabs(acc);
	double t_dec = fabs(dec);
	
	//std::cout<<"t_acc"<<t_acc<<" t_dec:"<<t_dec<<std::endl;
	//std::cout<<"set:"<<set<<std::endl;
	

	if ( (set * current) < 0)
	{//diff speed dir, use dec
	
		//current negative speed
		if( current < 0 ){
			if ( (current + t_dec) < set)
			{
				set = current + t_dec;
				return set;
			}else{
				return set;
			}
			
		}else{//positive speed

			if ( ( current - t_dec) > set)
			{
				set = current - t_dec;
				return set;
			}else{
				return set;
			}
		}

	}else{// same speed dir
		
		//if increase
		if(fabs(set) > fabs(current)){
			
			//current negative speed increase
			if( (current < 0 ) || ( set < 0 )){
				
				if( (current - t_acc) > set ){
					set = current - t_acc;
					return set;
				}else{
					return set;
				}

			}else{//positive speed increase

				if( ( current + t_acc ) < set ){
					set = current + t_acc;
					return set;
				}else{
					
					return set;
				}
			}
		}//decrease
		else{
			//current negative speed decrease
			if( (current < 0 ) || ( set < 0 )){
				if( ( current + t_dec ) < set ){
					set = current + t_dec;
					return set;
				}else{
					return set;
				}
			}else{//positive speed decrease
				if( ( current - t_dec ) > set ){
					set = current - t_dec;
					return set;
				}else{
					return set;
				}
			}
		}

		
	}

	


	
	return set;

}
