#include <iostream>
#include <array>
#include <string>
using namespace std;

double parse_double(char* var);
double ran_gen();
double exp_time_gen(double param);
bool input_packet(double prob_array[], int curr_packet);
double min_time(double input, double output);
void zero_array(double array[], int n);

int main(int argc, char* argv[]) {
    //Variable declaration
    //Assist Variables
    double next_input, next_output, overtime, T_last;
    int max_packets = argc - 4;
    int curr_packets = 0;
    double*  prob_array = new double[max_packets];
    //Inputs
    double T_init, gamma, mu;
    //Outputs
    double T_curr = 0.0, T_wait, T_service, gamma_A;
    int X = 0,Y = 0;
    double* amount_packets_time = new double[max_packets];
    zero_array(amount_packets_time, max_packets);

    //Parsing the input
    T_init = parse_double(argv[1]);
    gamma = parse_double(argv[2]);
    mu = parse_double(argv[3]);

    for(int i = 0; i < max_packets; i++)
    {
        prob_array[i] = parse_double(argv[i+4]);
    }

    //Using initial time;
    overtime = T_init + 1.0;
    next_input = overtime;
    next_output = overtime;
    T_last = 0;

    //Loop for active listening time
    while(T_curr <= T_init) {

        amount_packets_time[curr_packets] += T_curr - T_last;
        T_last = T_curr;

        if (T_curr == next_input)
        {
            if (input_packet(prob_array, curr_packets))
            {
                curr_packets++;
            }
            else
            {
                X++;
            }
            next_input = overtime;
        }

        if (T_curr == next_output)
        {
            curr_packets--;
            Y++;
            next_output = overtime;
        }

        if (next_input == overtime && curr_packets < max_packets)
        {
            next_input = T_curr + exp_time_gen(gamma);
        }

        if (next_output == overtime && curr_packets > 0)
        {
            next_output = T_curr + exp_time_gen(mu);
        }

        T_curr = min_time(next_input, next_output);
    }

    T_curr = next_output;

    //Loop for after listening time
    while(curr_packets > 0)
    {
        amount_packets_time[curr_packets] += T_curr - T_last;
        T_last = T_curr;

        if (T_curr == next_output)
        {
            curr_packets--;
        }
        next_output = T_curr + exp_time_gen(mu);
        T_curr = next_output;
    }

    return 0;
}

double parse_double(char* var)
{
    string string_var(var);

    return stod(string_var);
}
 double ran_gen ()
 {
    return ((double)rand() / (double)(RAND_MAX + 1));
 }

 double exp_time_gen(double param)
 {
    double time = 0;
    time = -(log(ran_gen())/ param);
    return time;
 }

 bool input_packet(double prob_array[], int curr_packet)
 {
    if (ran_gen() <= prob_array[curr_packet])
        return true;
    return false;
 }

 double min_time (double input, double output)
 {
    if (input < output)
        return input;
    return output;
 }

 void zero_array(double array[], int n)
 {
    for (int i = 0; i < n; i ++)
        array[i] = 0.0;
 }