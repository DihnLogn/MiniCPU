#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class CPU {
private:
    int R0 = 0;
    int R1 = 0;
    int R2 = 0;
    int R3 = 0;

    int PC = 0;

    bool zeroFlag = false;

    int RAM[256] = {};

    std::vector<std::string> program;

public:

    CPU(std::vector<std::string> instructions) {
        program = instructions;
    }

    int getRegister(std::string name) {

        if (name == "R0") return R0;
        if (name == "R1") return R1;
        if (name == "R2") return R2;
        if (name == "R3") return R3;

        return 0;
    }

    void setRegister(std::string name, int value) {

        if (name == "R0") R0 = value;
        else if (name == "R1") R1 = value;
        else if (name == "R2") R2 = value;
        else if (name == "R3") R3 = value;
    }

    void execute(std::string instruction) {

        std::stringstream ss(instruction);

        std::string command;
        std::string operand1;
        std::string operand2;

        ss >> command >> operand1 >> operand2;

        // =========================
        // MOV
        // =========================

        if (command == "MOV") {

            int value = std::stoi(operand2);

            setRegister(operand1, value);

            PC++;
        }

        // =========================
        // ADD
        // =========================

        else if (command == "ADD") {

            int value1 = getRegister(operand1);
            int value2 = getRegister(operand2);

            setRegister(operand1, value1 + value2);

            PC++;
        }

        // =========================
        // SUB
        // =========================

        else if (command == "SUB") {

            int value1 = getRegister(operand1);
            int value2 = getRegister(operand2);

            setRegister(operand1, value1 - value2);

            PC++;
        }

        // =========================
        // STORE
        // =========================

        else if (command == "STORE") {

            int address = std::stoi(operand2);

            RAM[address] = getRegister(operand1);

            PC++;
        }

        // =========================
        // LOAD
        // =========================

        else if (command == "LOAD") {

            int address = std::stoi(operand2);

            setRegister(
                operand1,
                RAM[address]
            );

            PC++;
        }

        // =========================
        // CMP
        // =========================

        else if (command == "CMP") {

            int value1 = getRegister(operand1);
            int value2 = getRegister(operand2);

            zeroFlag = (value1 == value2);

            PC++;
        }

        // =========================
        // JMP
        // =========================

        else if (command == "JMP") {

            PC = std::stoi(operand1);
        }

        // =========================
        // JZ
        // =========================

        else if (command == "JZ") {

            int address = std::stoi(operand1);

            if (zeroFlag) {
                PC = address;
            }
            else {
                PC++;
            }
        }

        // =========================
        // Unknown command
        // =========================

        else {

            std::cout << "Unknown instruction: "
                      << command
                      << std::endl;

            PC++;
        }
    }

    void run() {

        while (PC < program.size()) {

            std::cout
                << "PC "
                << PC
                << " -> "
                << program[PC]
                << std::endl;

            execute(program[PC]);
        }
    }

    void displayState() {

        std::cout << std::endl;
        std::cout << "============================"
                  << std::endl;

        std::cout << "        CPU STATE"
                  << std::endl;

        std::cout << "============================"
                  << std::endl;

        std::cout << "R0 = " << R0 << std::endl;
        std::cout << "R1 = " << R1 << std::endl;
        std::cout << "R2 = " << R2 << std::endl;
        std::cout << "R3 = " << R3 << std::endl;

        std::cout << "PC = " << PC << std::endl;

        std::cout << "Zero Flag = "
                  << zeroFlag
                  << std::endl;

        std::cout << "RAM[100] = "
                  << RAM[100]
                  << std::endl;

        std::cout << "============================"
                  << std::endl;
    }
};


int main() {

    // =========================
    // PROGRAM
    // =========================

    std::vector<std::string> program = {

        "MOV R0 10",
        "MOV R1 20",
        "ADD R0 R1",
        "STORE R0 100",
        "LOAD R2 100",
        "CMP R0 R2",
        "JZ 8",
        "MOV R3 999",
        "MOV R3 123"
    };

    // =========================
    // CREATE CPU
    // =========================

    CPU cpu(program);

    // =========================
    // RUN PROGRAM
    // =========================

    cpu.run();

    // =========================
    // SHOW CPU
    // =========================

    cpu.displayState();

    return 0;
}