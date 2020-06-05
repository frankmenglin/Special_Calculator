#include <iostream>
#include <cmath>
using namespace std;

double Binary_Put_Option(double S,double K, double sigma, double r, double delta, double t, int step){
    // S=spot,K=strike, sigma=volatility, r=interest rate, delta=dividend rate
    // t=time to expiration, step=number of time step
    double h=t/double(step); //size of time step
    double u=exp((r-delta)*h+sigma*sqrt(h)); //How much price go up in 1 step
    double d=exp((r-delta)*h-sigma*sqrt(h)); //How much price go down in 1 step
    double p=(exp((r-delta)*h)-d)/(u-d); //Risk-Neutral probability of price increasing in a step
    double q=1.0-p; //Risk Neutral probability of price decreasing in a step

    double price_at_expiration [step+1]; //An array that contain possible prices of the underlying at expiration
    double lowest_price=S*pow(d,step);

    for (int i = 0; i <=step; i++) {
    price_at_expiration[i]=lowest_price*pow(u,i)/pow(d,i);
    }//All possible prices of underlying at expiration

    double put_price [step+1]; //Binary Call option price array
    for (int i = 0; i <=step; i++) {
    if (price_at_expiration[i]>K){
        put_price[i]=0.0;
    }else{
        put_price[i]=1.0;}
    }//Initialized the array by containing all possible binary call option prices at expiration

    for (int j=1; j<=step ;j++){
            for (int i=0; i<=step-j;i++){
                put_price[i]=(put_price[i]*q+put_price[i+1]*p)*exp(-r*h);
            }
    }
    return put_price[0];
}
double normalCDF(double x) // Phi(-¡Û, x) aka N(x)
{
    return std::erfc(-x/std::sqrt(2))/2;
}
double Binary_Put_Option_continuous(double S,double K, double sigma, double r, double delta, double t){
    double d1;
    double d2;
    d1=(log(S/K)+(r-delta+0.5*pow(sigma,2))*t)/(sigma*pow(t,0.5));
    d2=(log(S/K)+(r-delta-0.5*pow(sigma,2))*t)/(sigma*pow(t,0.5));
    return exp(-r*t)*(1-normalCDF(d2));
}//Pricing using continuous model
int main()
{
    cout << Binary_Put_Option(40,40,0.3,0.08, 0.00, 1, 5000)<< endl;
    //S,K,sigma,r,delta,T-t,total time steps
    cout << Binary_Put_Option_continuous(40,40,0.3,0.08, 0.00, 1);
	return 0;
}
