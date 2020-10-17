int FactorialSum(List L)
{
    int Fact,Sum,i;
    PtrToNode = L;

    Sum = 0;
    while (P)
    {
        Fact = 1;
        for ( i = 2; i <= P->data ; i++)
        {
            Fact *= i;
            Sum += Fact;
            P = P->next;
        }
        
    }
    return Sum;
    
}