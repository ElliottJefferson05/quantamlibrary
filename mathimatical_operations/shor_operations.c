#include <stddef.h>
#include "shor_operations.h"
#include "core_operations.h"

#define pi 3.14159265358979323846

void quantom_Forier_Transform(Quantom_register *q, int length)
{

    for (int i = 0; i < length; i++)
    {

        quantom_hadamard(q, i);

        int k = 2;

        for (int j = i + 1; j < length; j++)
        {
            controlled_Phase(q, j, i, pi / k);
            k *= 2;
        }
    }

    int p = length - 1;

    for (int h = 0; h < length / 2; h++)
    {
        Swap(q, h, p);
        p--;
    }
}

void inverse_Quantum_Forier_Transform(Quantom_register *q, int length)
{

    if (q == NULL)
    {
        return;
    }

    if (q->num_of_qbits <= 0)
    {
        return;
    }

    if (q->state_size < 0)
    {
        return;
    }

    int p = length - 1;

    for (int h = 0; h < length / 2; h++)
    {
        Swap(q, h, p);
        p--;
    }

    for (int i = length - 1; i >= 0; i--)
    {

        int k = 2;

        for (int j = i + 1; j < length; j++)
        {
            controlled_Phase(q, j, i, -pi / k);
            k *= 2;
        }

        quantom_hadamard(q, i);
    }
}

void quantom_Forier_Transform_Range(Quantom_register *q, int start, int length)
{
    if (q == NULL || q->state == NULL)
    {
        return;
    }

    if (start < 0 || length <= 0)
    {
        return;
    }

    if (start + length > q->num_of_qbits)
    {
        return;
    }

    int end = start + length;

    for (int i = start; i < end; i++)
    {

        quantom_hadamard(q, i);

        int k = 2;

        for (int j = i + 1; j < end; j++)
        {
            controlled_Phase(q, j, i, pi / k);
            k *= 2;
        }
    }

    int left = start;
    int right = end - 1;

    while (left < right)
    {
        Swap(q, left, right);

        left++;
        right--;
    }
}

void inverse_Quantum_Forier_Transform_Range(Quantom_register *q, int start, int length)
{
    if (q == NULL || q->state == NULL)
    {
        return;
    }

    if (start < 0 || length <= 0)
    {
        return;
    }

    if (start + length > q->num_of_qbits)
    {
        return;
    }

    int end = start + length;

    int left = start;
    int right = end - 1;

    while (left < right)
    {
        Swap(q, left, right);

        left++;
        right--;
    }

    for (int i = end - 1; i >= start; i--)
    {

        int k = 2;

        for (int j = i + 1; j < end; j++)
        {
            controlled_Phase(q, j, i, -pi / k);
            k *= 2;
        }

        quantom_hadamard(q, i);
    }
}
int gcd(int a, int b)
{

    if (a < 0)
    {
        a = -a;
    }

    if (b < 0)
    {
        b = -b;
    }

    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

void MAJ(Quantom_register *q, int target1, int target2, int control)
{
    quantom_CNOT(q, target1, target2);
    quantom_CNOT(q, target1, control);
    Toffoli(q, control, target2, target1);
}

void UMA(Quantom_register *q, int target1, int target2, int control)
{
    Toffoli(q, control, target2, target1);
    quantom_CNOT(q, target1, control);
    quantom_CNOT(q, control, target2);
}

void Ripple_Adder(Quantom_register *q, int a_start, int b_start, int carry, int carry_out, int length)
{

    if (q == NULL || q->state == NULL)
    {
        return;
    }

    if (length <= 0)
    {
        return;
    }

    MAJ(q, a_start, b_start, carry);

    for (int i = 1; i < length; i++)
    {

        MAJ(q, a_start + i, b_start + i, a_start + i - 1);
    }

    quantom_CNOT(q, a_start + length - 1, carry_out);

    for (int i = length - 1; i >= 1; i--)
    {

        UMA(q, a_start + i, b_start + i, a_start + i - 1);
    }

    UMA(q, a_start, b_start, carry);
}

void inverse_MAJ(Quantom_register *q, int target1, int target2, int control)
{

    Toffoli(q, control, target2, target1);
    quantom_CNOT(q, target1, control);
    quantom_CNOT(q, target1, target2);
}

void inverse_UMA(Quantom_register *q, int target1, int target2, int control)
{

    quantom_CNOT(q, control, target2);
    quantom_CNOT(q, target1, control);
    Toffoli(q, control, target2, target1);
}

void Subtraction(Quantom_register *q, int a_start, int b_start, int carry, int carry_out, int length)
{

    if (q == NULL || q->state == NULL)
    {
        return;
    }

    if (length <= 0)
    {
        return;
    }

    inverse_UMA(q, a_start, b_start, carry);

    for (int i = 1; i < length; i++)
    {

        inverse_UMA(q, a_start + i, b_start + i, a_start + i - 1);
    }

    quantom_CNOT(q, a_start + length - 1, carry_out);

    for (int i = length - 1; i >= 1; i--)
    {

        inverse_MAJ(q, a_start + i, b_start + i, a_start + i - 1);
    }

    inverse_MAJ(q, a_start, b_start, carry);
}

void controlled_N_To_Zero(Quantom_register *q, int n_start, int t, int N, int length)
{

    for (int i = 0; i < length; i++)
    {

        int n_bit = 1 << i;

        if ((N & n_bit) != 0)
        {

            quantom_CNOT(q, t, n_start + i);
        }
    }
}

void adderModulo(Quantom_register *q, int a_start, int b_start, int n_start, int carry, int carry_out, int t, int N, int length)
{

    if (q == NULL || q->state == NULL)
    {
        return;
    }

    Ripple_Adder(q, a_start, b_start, carry, carry_out, length);

    Subtraction(q, n_start, b_start, carry, carry_out, length);

    quantom_CNOT(q, carry_out, t);

    quantom_X(q, t);

    controlled_N_To_Zero(q, n_start, t, N, length);

    Ripple_Adder(q, n_start, b_start, carry, carry_out, length);

    controlled_N_To_Zero(q, n_start, t, N, length);

    Subtraction(q, a_start, b_start, carry, carry_out, length);

    quantom_CNOT(q, carry_out, t);

    Ripple_Adder(q, a_start, b_start, carry, carry_out, length);
}



void loadControlledConstant(Quantom_register *q, int control, int x_bit, int temp_start, int value, int length){

    for(int i = 0; i < length; i++){

        int value_bit = 1 << i;

        if((value & value_bit) != 0){

            Toffoli(q,control,x_bit,temp_start + i);

        }
    }
}


void controlledMultiplierModulo(Quantom_register *q, int control, int x_start, int result_start, int temp_start, int n_start, int carry, int carry_out, int t, int a, int N, int length){

    if(q == NULL || q->state == NULL){
        return;
    }

    int value = a % N;

    for(int i = 0; i < length; i++){

        loadControlledConstant(q,control,x_start + i,temp_start,value,length);

        adderModulo(q,temp_start,result_start,n_start,carry,carry_out,t,N,length);

        loadControlledConstant(q,control,x_start + i,temp_start,value,length);

        value = (value * 2) % N;
    }

    quantom_X(q,control);

    for(int i = 0; i < length; i++){

        Toffoli(q,control,x_start + i,result_start + i);

    }

    quantom_X(q,control);
}


void Swap_Registers(Quantom_register *q, int register1_start, int register2_start, int length){

    if(q == NULL || q->state == NULL){
        return;
    }

    for(int i = 0; i < length; i++){

        Swap(q,register1_start + i,register2_start + i);

    }
}

int modularInverse(int a, int N){

    int t = 0;
    int new_t = 1;

    int r = N;
    int new_r = a;

    while(new_r != 0){

        int quotient = r / new_r;

        int temp_t = t;
        t = new_t;
        new_t = temp_t - quotient * new_t;

        int temp_r = r;
        r = new_r;
        new_r = temp_r - quotient * new_r;
    }

    if(r > 1){
        return -1;
    }

    if(t < 0){
        t += N;
    }

    return t;
}

void inverseAdderModulo(Quantom_register *q, int a_start, int b_start, int n_start, int carry, int carry_out, int t, int N, int length){

    if(q == NULL || q->state == NULL){
        return;
    }

    Subtraction(q,a_start,b_start,carry,carry_out,length);

    quantom_CNOT(q,carry_out,t);

    Ripple_Adder(q,a_start,b_start,carry,carry_out,length);

    controlled_N_To_Zero(q,n_start,t,N,length);

    Subtraction(q,n_start,b_start,carry,carry_out,length);

    controlled_N_To_Zero(q,n_start,t,N,length);

    quantom_X(q,t);

    quantom_CNOT(q,carry_out,t);

    Ripple_Adder(q,n_start,b_start,carry,carry_out,length);

    Subtraction(q,a_start,b_start,carry,carry_out,length);
}

void inverseControlledMultiplierModulo(Quantom_register *q, int control, int x_start, int result_start, int temp_start, int n_start, int carry, int carry_out, int t, int a, int N, int length){

    if(q == NULL || q->state == NULL){
        return;
    }

    quantom_X(q,control);

    for(int i = length - 1; i >= 0; i--){

        Toffoli(q,control,x_start + i,result_start + i);

    }

    quantom_X(q,control);

    for(int i = length - 1; i >= 0; i--){

        int value = a % N;

        for(int j = 0; j < i; j++){

            value = (value * 2) % N;

        }

        loadControlledConstant(q,control,x_start + i,temp_start,value,length);

        inverseAdderModulo(q,temp_start,result_start,n_start,carry,carry_out,t,N,length);

        loadControlledConstant(q,control,x_start + i,temp_start,value,length);

    }
}

void modularExponentiation(Quantom_register *q, int exponent_start, int exponent_length, int result_start, int work_start, int temp_start, int n_start, int carry, int carry_out, int t, int a, int N, int length){

    if(q == NULL || q->state == NULL){
        return;
    }
    
    quantom_X(q,result_start);

    int value = a % N;

    for(int i = 0; i < exponent_length; i++){

        int inverse = modularInverse(value,N);

        if(inverse == -1){
            return;
        }

        controlledMultiplierModulo(q,exponent_start + i,result_start,work_start,temp_start,n_start,carry,carry_out,t,value,N,length);

        Swap_Registers(q,result_start,work_start,length);

        inverseControlledMultiplierModulo(q,exponent_start + i,result_start,work_start,temp_start,n_start,carry,carry_out,t,inverse,N,length);

        value = (value * value) % N;
    }
}