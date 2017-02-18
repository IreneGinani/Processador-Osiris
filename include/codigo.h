#ifndef _CODIGO_
#define _CODIGO_

#include <iostream>
#include <string>
#include <vector>

class Codigo
{
    private:
        std::string m_name;
        std::string m_dest;
        std::string m_op1;
        std::string m_op2;
        

    public:
        Codigo( std::string );
        std::string getNome( );
        std::string getDest( );
        std::string getOp1( );
        std::string getOp2( );
        void setNome(std::string teste );
        void setDest(std::string teste );
        void setOp1(std::string teste );
        void setOp2(std::string teste );
};

#endif