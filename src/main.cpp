#include <systemc.h>
#include "ula.h"
#include "data.h"
#include "controller.h"
#include "data_memory.h"

int main(int argc, char* argv[]) {
    sc_clock clock("clock", 10, SC_NS, 1, 10, SC_NS);

    sc_signal<sc_uint<32> > result, data_out, data_in;
    sc_signal<sc_uint<32> > op1, op2;
    sc_signal<sc_uint<4>> op_code;
    sc_signal<sc_uint<32> > addr, addr_memory;
    sc_signal< bool > enable, z, n, operation;

    controller ctl("controller");
    ctl.clock(clock);
    ctl.counter_out(addr);
    ctl.enable(enable);
    ctl.op(op_code);
    ctl.regA(op1);
    ctl.z(z);
    ctl.n(n);

    data data("data");
    data.regA(op1);
    data.regB(op2);
    data.op_code(op_code);
    data.Clk(clock);
    data.addr(addr);
    data.enable(enable);

    ula ula("ula");
    ula.regDest(result);
    ula.regA(op1);
    ula.regB(op2);
    ula.op_code(op_code);
    ula.z(z);
    ula.n(n);
    ula.operation(operation);
    ula.data_mem_in(data_in);
    ula.data_mem_out(data_out);
    ula.addr(addr_memory);

    data_memory memory("memory");
    memory.addr(addr_memory);
    memory.data_in(data_in);
    memory.data_out(data_out);
    memory.Clk(clock);
    memory.operation(operation);

    sc_start();  // Run the simulation till sc_stop is encountered

    return 0;// Terminate simulation
}