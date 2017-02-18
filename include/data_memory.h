//
// Created by Gabriela on 30/11/16.
//

#include <systemc.h>
#include <iostream>
#include <fstream>

SC_MODULE(data_memory) {
    sc_out < sc_uint<32> > data_out;
    sc_in < sc_uint<32> > data_in;
    sc_in<sc_uint<32> > addr;
    sc_in<bool> operation;

    sc_in<bool> Clk;

    std::vector<std::string> data_mem;

    void load_memory() {
        int current_line = 0;
        std::string word;
        std::string aux;
        std::ifstream arquivo("regs.txt", std::fstream::in);

        std::vector<Codigo> line;
        while (!arquivo.eof()) {
            current_line++;
            std::getline(arquivo, word);

            if (!word.empty()) {
                for (auto i(0u); i < word.length(); ++i) {
                    if (word[i] == ' ' or word[i] == ',')
                        continue;
                    else {
                        while (word[i] != ' ' and word[i] != ',' and i < word.length()) {
                            aux += word[i++];
                        }
                        data_mem.push_back(aux);
                        aux = "";
                    }
                }
            }
        }
        arquivo.close();
    }

    void write_memory() {
        if (operation.read()) {
            data_mem.at(addr.read()) = data_in.read();
        }
    }

    void read_memory() {
        if (not operation.read()) {
            data_out.write(stoi(data_mem.at(addr.read())));
        }
    }

    SC_CTOR(data_memory)   {
        SC_METHOD(load_memory);
        SC_METHOD(write_memory);
        SC_METHOD(read_memory);

        sensitive << addr << operation << data_in << Clk;
    }
};
