#include <iostream>

using namespace std;

// Program that will iteratively update and predict
// based on the location measurements
// and inferred motions shown below

enum{new_mean, new_var};

// Measurement Update
float * update(float mean1, float var1, float mean2, float var2){
    float * new_info=new float[2];
    new_info[new_mean]=float(var2*mean1+var1*mean2)/(var1+var2);
    new_info[new_var]=1./(1./var1+1./var2);

    return new_info;
}

// Motion Update
float * predict(float mean1, float var1, float mean2, float var2){
    float * new_info=new float[2];
    new_info[new_mean]=mean1+mean2;
    new_info[new_var]=var1+var2;
    
    return new_info;
}

int main(){
    float measurements[5]={5.,6.,7.,9.,10.};
    float motion[5]={1.,1.,2.,1.,1.};

    float measurements_sig=4.;
    float motion_sig=2.;
    float mu=0.;
    float sig=10000.;

    float * new_info=new float[2];

    for(int i=0;i<5;i++){
        new_info=predict(motion[i],motion_sig,mu,sig);
        mu=new_info[0]; sig=new_info[1];
        new_info=update(measurements[i],measurements_sig,mu,sig);
        mu=new_info[0]; sig=new_info[1];    
    }

    cout<<mu<<", "<<sig;
}
