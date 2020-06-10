#include "queue.hpp"

int main() {

    srand(time(NULL));

    double Time = 0;
    double T1_min = 0, T1_max = 6, T2_min = 0, T2_max = 1;
    double prob = 0.8;
    int report_count = 1000;

    // cout << ">> T1_min >> T1_max >> T2_min >> T2_max" << endl;
    // cin >> T1_min >> T1_max >> T2_min >> T2_max;

    if (T1_min > T1_max || T2_min > T2_max) {
        cout << "time difficulties" << endl;
        return 1;
    }

    int report_in = 0; // заявок вошло в систему
    int report_out = 0; // заявок вышло из системы

    queue* Q = new queue();

    AO* myAO = new AO();

    double next_push_time = 0;
    double next_pop_time = INF;

    double sum_waiting_time = 0;
    double max_waiting_time = 0;
    int max_waiting_id = -1;

    int AO_report_count = 0;

    double OA_work_time = 0;

    cout << setw(18) << "report_in"
        << setw(20) << "Queue length"
        << setw(25) << "max waiting time"
        << setw(25) << "max waiting id"
        << setw(25) << "average waiting time"
        << endl;
    

    while (true) {

        

        if (Q->is_empty() && myAO->is_empty() && report_in == report_count) {

            cout << endl;
            cout << setw(18) << "simulation time" << setw(10) << Time << endl;
            cout << setw(18) << "wasted AO time" << setw(10) << (Time - OA_work_time < EPS ? 0 : Time - OA_work_time) << endl;
            cout << setw(18) << "reports passed AO" << setw(10) << AO_report_count << endl;

            return 0;
        }

        if ((!(Q->is_empty())) && myAO->is_empty()) {
            
            myAO->push(Q->pop());
            next_pop_time = T2_min + ((double)rand() / RAND_MAX) * (T2_max - T2_min);

            OA_work_time += next_pop_time;

            myAO->in_process->entry_time += next_pop_time; //уменьшение времени ожидания



        } else if (next_push_time <= next_pop_time && report_in != report_count) {
            
            if ((report_in != report_count) != (next_push_time != INF)) cout << "logic error1" << endl;

            next_pop_time -= (next_pop_time != INF ? next_push_time : 0);

            Time += next_push_time;
            Q->push(++report_in, Time);

            next_push_time = (report_in != report_count ? T1_min + ((double)rand() / RAND_MAX) * (T1_max - T1_min) : INF);

        } else if (next_push_time > next_pop_time && next_pop_time != INF) {

            next_push_time -= (next_push_time != INF ? next_pop_time : 0);
            Time += next_pop_time;
            next_pop_time = INF;
            
            queue_unit* temp = myAO->pop();
            AO_report_count++;

            if ((double)rand() / RAND_MAX < prob) {
                
                Q->add(temp);

            } else {
                report_out++;

                sum_waiting_time += Time - temp->entry_time;

                if (max_waiting_time < Time - temp->entry_time) {
                    max_waiting_time = Time - temp->entry_time;
                    max_waiting_id = temp->id;
                }

                if (report_out % 100 == 0) {
                    cout << setw(18) << report_in
                        << setw(20) << Q->length
                        << setw(25) << max_waiting_time
                        << setw(25) << max_waiting_id
                        << setw(25) << sum_waiting_time / report_in
                        << endl;
                }

                //free(temp);
            }

        } else {
            cout << "logic error2" << endl;
            return 0;
        }
    } 

    
    return 0;
}