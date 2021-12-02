#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int depth_1 = 0, depth_2=0, forward = 0, aim = 0;

void inc_solver(int operation, int steps)
{
    asm volatile
    (
        "MOVL %0,   %%ebx\n\t" // Copy the operation to EBX register
        "MOVL %1,   %%ecx\n\t" // Copy the steps to ECX register
        "CMP $0x75, %%ebx\n\t" // Check if letter is 'u' (UP) (0x75 = 'u' ascii code)
        "JZ UP\n\t"            // Do UP
        "CMP $0x64, %%ebx\n\t" // Check if letter is 'd' (DOWN) (0x64 = 'd' ascii code)
        "JZ DOWN\n\t"          // Do DOWN
        "JMP FORWARD\n\t"      // Else, do FORWARD
        "UP:\n\t"              // 1) UP:
        "MOVL %2, %%eax\n\t"   // -- Decrease depth_1 by steps
        "SUBL %%ecx, %%eax\n\t"
        "MOVL %%eax, %2\n\t"
        "MOVL %5, %%eax\n\t"   // -- Descrease aim by steps
        "SUBL %%ecx, %%eax\n\t"
        "MOVL %%eax, %5\n\t"
        "JMP END\n\t"
        "DOWN:\n\t"            // 2) DOWN:
        "MOVL %2, %%eax\n\t"   // -- Increase depth_1 by steps
        "ADDL %%ecx, %%eax\n\t"
        "MOVL %%eax, %2\n\t"
        "MOVL %5, %%eax\n\t"   // -- Increase aim by steps
        "ADDL %%ecx, %%eax\n\t"
        "MOVL %%eax, %5\n\t"
        "JMP END\n\t"
        "FORWARD:\n\t"         // 3) FORWARD:
        "MOVL %3, %%eax\n\t"   // -- Increase forward by steps
        "ADDL %%ecx, %%eax\n\t"
        "MOVL %%eax, %3\n\t"
        "MOVL %5, %%eax\n\t"   // -- Increase depth_2 by aim * steps
        "MOVL %%ecx, %%ebx\n\t"
        "IMUL %%ebx, %%eax\n\t"
        "ADDL %4, %%eax\n\t"
        "MOVL %%eax, %4\n\t"
        "END:\n\t"
        :"=m"(operation), "=m"(steps), "=m"(depth_1), "=m"(forward), "=m"(depth_2), "=m"(aim)
        :"m"(depth_1), "m"(forward), "m"(depth_2), "m"(aim)
    );
}

int main() {
    FILE* data;
    char* line;
    size_t size = 0;
    ssize_t read;

    data = fopen("d2_data.txt", "r");
    while ((read = getline(&line, &size, data)) != -1)
        inc_solver( strtok( line, " ")[0], atoi( strtok( 0x0, " ") ) );
    fclose(data);

    printf("Part 1: %i\n", depth_1 * forward);
    printf("Part 2: %i\n", depth_2 * forward);
}
