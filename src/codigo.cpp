#include "../include/codigo.h"

Codigo::Codigo( std::string linha_instrucao ) : m_name( "NULL" ), m_dest( "NULL" ), m_op1( "NULL" ), m_op2 ( "NULL" )
{
    std::string aux = "";
    std::vector<std::string> token; 
    if (linha_instrucao == ""){
        return ;
    }
    for(auto i (0u); i < linha_instrucao.length(); ++i)
    {
        if(linha_instrucao[i] == ' ' or linha_instrucao[i] == ',')
            continue;
        else 
        {
            while(linha_instrucao[i] != ' ' and linha_instrucao[i] != ',' and i < linha_instrucao.length())
            {
                aux += linha_instrucao[i++];
            }
            token.push_back(aux);
            aux = "";
        }        
    }
    
    if(token[0] == "lw" or token[0] == "ld" or token[0] == "addi" or token[0] == "subi")
    {
        if(((token[0] == "lw" or token[0] == "ld") and token.size() < 3) or  ((token[0] == "addi" or token[0] == "subi") and token.size() < 4 ))
        {
            std::cout << "Formato inválido: " << token[0] << std::endl;
        }
        else 
        {
            m_name = token[0];
            m_dest = token[1];
            m_op1 = token[2];
            m_op2 = "";
        }
    }
    else if (token[0] == "add" or token[0] == "sub")
    {
        if(token.size() < 4)
        {
            std::cout << "Formato inválido: " << token[0] << std::endl;
        }
        else
        {
            m_name = token[0];
            m_dest = token[1];
            m_op1 = token[2];
            m_op2 = token[3];
        }

    }
    else if(token[0] == "sw" or token[0] == "st")
    {
        if(token.size() < 3)
        {
            std::cout << "Formato inválido: " << token[0] << std::endl;
        }
        else 
        {
            m_name = token[0];
            m_dest = token[2];
            m_op1 = token[1];
            m_op2 = "";
        }
    }
    else if(token[0] == "beq" or token[0] == "bne")
    {
        if(token.size() < 4)
        {
            std::cout << "Formato inválido: " << token[0] << std::endl;
        }
        else 
        {
            m_name = token[0];
            m_op1 = token[1];
            m_op2 = token[2];
            m_dest = token[3]; // destino + posicao de memoria atual
        }
    }
    else if(token[0] == "j" or token[0] == "jz" or token[0] == "jn")
    {
        if(token.size() < 2)
        {
            std::cout << "Formato inválido: " << token.size() << std::endl;
        }
        else 
        {
            m_name = token[0];
            m_op1 = "";
            m_op2 = "";
            m_dest = token[1];
        }
    }
    else if(token[0] == "mult" and token[1] != "lo")
    {
        if(token.size() < 3)
        {
            std::cout << "Formato inválido: " << token[0] << std::endl;
        }
        else
        {
            m_name = token[0];
            m_dest = "lo";
            m_op1 = token[1];
            m_op2 = token[2];
        }
    }
    else if (token[0] == "and" or token[0] == "or" or token[0] == "xor")
    {
        if (token.size() < 4)
        {
            std::cout << "Formato inválido: " << token[0] << std::endl;
        }else {
            m_name = token[0];
            m_dest = token[1];
            m_op1 = token[2];
            m_op2 = token[3];
        }
    }
    else if (token[0] == "cmp") {
        m_name = token[0];
        m_op1 = token[2];
        m_op2 = token[3];
    }
    else if (token[0] == "not") {
        m_name = token[0];
        m_op1 = token[1];
        m_op2 = "";
        m_dest = token[2];
    }
    else if (token[0] == "jump:") {
        m_name = token[0];
    }
    else
    {
        if(token.size() < 4)
        {
            std::cout << "Formato inválido: " << token[0] << std::endl;
        }
        else
        {
            m_name = token[0];
            m_dest = token[1];
            m_op1 = token[2];
            m_op2 = token[3];
        }
    }
}

std::string 
	Codigo::getNome()
	{ 
		return m_name; 
	}

std::string 
	Codigo::getDest()
	{ 
		return m_dest; 
	}

std::string 
	Codigo::getOp1()
	{ 
		return m_op1; 
	}

std::string 
	Codigo::getOp2()
	{ 
		return m_op2; 
	}
void 
    Codigo::setNome(std::string nome)
    { 
        m_name = nome; 
    }

void 
    Codigo::setDest(std::string dest)
    { 
        m_dest = dest; 
    }

void
    Codigo::setOp1(std::string op1)
    { 
        m_op1 = op1; 
    }

void 
    Codigo::setOp2(std::string op2)
    { 
        m_op2 = op2; 
    }

