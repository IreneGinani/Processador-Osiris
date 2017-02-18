#include "systemc.h"

SC_MODULE (controller) {
    sc_in_clk     clock ;
    sc_out<sc_uint<32> > counter_out;
    sc_in<bool> enable;

    sc_in < sc_uint<32> > regA;
    sc_in <sc_uint<4>> op;
    sc_uint<32>	count;

    sc_in<bool> n;
    sc_in<bool> z;

    void incr_count () {
        while (true) {
            wait();
            if (enable.read() == true) {
                if (op.read() == 8 or op.read() == 9 or op.read() == 10) {
                    if (op.read() == 9 and n.read() == true)
                        count = regA.read();
                    else if (op.read() == 9)
                        count += 1;
                    else if (op.read() == 10 and z.read() == true)
                        count = regA.read();
                    else if (op.read() == 10)
                        count += 1;
                    else
                        count = regA.read();
                } else {
                    count += 1;
                }
                counter_out.write(count);
            } else sc_stop();
        }

    }
    void print_count () {
        while (true) {
            wait();
            cout << "@" << sc_time_stamp() << " :: Counter Value " << counter_out.read() <<endl;
        }
    }

    SC_CTOR(controller) {
        std::cout << "starting processor..." << std::endl;
        cout << "@" << sc_time_stamp() << " :: Counter Value 0" << endl;

        SC_CTHREAD(incr_count, clock.pos());
        SC_THREAD(print_count);

        sensitive << counter_out;
    }
};