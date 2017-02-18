//
// Created by Gabriela on 30/11/16.
//

#include <systemc.h>

SC_MODULE (ula) {
        sc_in<sc_uint<32>> regA, regB;
        sc_out<sc_uint<32>> regDest;

        sc_in<sc_uint<4>> op_code;

        sc_uint<32> dataA, dataB, res;
        sc_out<bool> n;
        sc_out<bool> z;

        sc_out<bool> operation;
        sc_out<sc_uint<32>> data_mem_in;
        sc_in<sc_uint<32>> data_mem_out;
        sc_out<sc_uint<32> > addr;

        void do_operation() {
            dataA = regA.read();
            dataB = regB.read();

            switch (op_code.read()) {
                case 1:
                    res = dataA + dataB;
                    cout << "@" << sc_time_stamp() << " | Sum >> (op1: "
                    << dataA << ") (op2: " << dataB << ") (res: " << res << ")" << endl;
                    break;
                case 2:
                    res = dataA - dataB;
                    if (dataA > dataB) {
                        n.write(true);
                    } else {
                        n.write(false);
                        if (res == 0) z.write(true);
                    }
                    cout << "@" << sc_time_stamp() << " | Sub >> (op1: "
                    << dataA << ") (op2: " << dataB << ") (res: " << res << ")" << endl;
                    break;
                case 3:
                    res = dataA && dataB;
                    cout << "@" << sc_time_stamp() << " | AND >> (op1: "
                    << dataA << ") (op2: " << dataB << ") (res: " << res << ")" << endl;
                    break;
                case 4:
                    res = dataA || dataB;
                    cout << "@" << sc_time_stamp() << " | OR >> (op1: "
                    << dataA << ") (op2: " << dataB << ") (res: " << res << ")" << endl;
                    break;
                case 5:
                    res = not (dataA || dataB);
                    cout << "@" << sc_time_stamp() << " | XOR >> (op1: "
                    << dataA << ") (op2: " << dataB << ") (res: " << res << ")" << endl;
                    break;
                case 6:
                    res = 0;
                    if (dataA > dataB) {
                        n.write(true);
                    } else if (dataA < dataB) {
                        n.write(false);
                    } else {
                        z.write(true);;
                        res = 1;
                    }
                    cout << "@" << sc_time_stamp() << " | Comp >> (op1: "
                    << dataA << ") (op2: " << dataB << ") (res: " << res << ")" << endl;
                    break;
                case 7:
                    res = not (dataA);
                    cout << "@" << sc_time_stamp() << " | Not >> (op: "
                    << dataA << ") (res: " << res << ")" << endl;
                    break;
                case 8:
                    cout << "@" << sc_time_stamp() << " | J >> (goto: "
                    << dataA << ")" << endl;
                    break;
                case 9: 
                    if (n == true)
                        cout << "@" << sc_time_stamp() << " | Jn >> (goto: "
                        << dataA << ")" << endl;
                    else
                        cout << "@" << sc_time_stamp() << " | Jn >> FALSE CONDITION" << endl;
                    break;
                case 10:
                    if (z == true)
                        cout << "@" << sc_time_stamp() << " | Jz >> (goto: "
                        << dataA << ")" << endl;
                    else
                        cout << "@" << sc_time_stamp() << " | Jz >> FALSE CONDITION" << endl;
                    break;
                case 11:
                    operation.write(false);
                    addr.write(dataB);
                    //data_mem_out.read();
                    cout << "@" << sc_time_stamp() << " | LW >> (read data: "
                    << dataA << ") reg to write: (" << dataB << ")" << endl;
                    break;
                case 12:
                    operation.write(true);
                    data_mem_in.write(dataA);
                    addr.write(dataB);
                    cout << "@" << sc_time_stamp() << " | SW >> (write data: "
                    << dataA << ") addres to write: (" << dataB << ")" << endl;
                    break;
            }
            regDest.write(res);
        }

        SC_CTOR(ula) {
            SC_METHOD(do_operation);
            sensitive << regA << regB << op_code;
        }
};

