bool somePredicate(double x)
    {
        return x < 0;
    }

bool anyTrue(const double a[], int n)
{
    if (n <= 0)
    {
        return true;
    }
    
    else if(n == 1)
    {
        return somePredicate(a[0]);
    }
    
    else
    {
        return somePredicate(a[0])
        &&anyTrue(a+1, n-1);
    }
}

int countTrue(const double a[], int n)
    {
        if (n <= 0)
        {
            return -1;
        }
        
        else if(n == 1)
        {
            return !somePredicate(a[0]);
        }
        
        else
        {
            return !somePredicate(a[0] + countTrue(a+1, n-1));
        }
    }

int firstTrue(const double a[], int n)
    {
       if (n <= 0)
       {
           return -1;
       }
        
        if(somePredicate(a[0]))
        {
            return 0;
        }
        
        if(firstTrue(a+1, n-1) == -1)
        {
            return -1;
        }
        
        return firstTrue(a+1, n-1) +1;
    }

int positionOfMax(const double a[], int n)
    {
        if (n <= 0)
        {
            return -1;
        }
        
        if (n == 1)
        {
            return 0;
        }
        
        int max = 1 + positionOfMax(a+1, n-1);
        
        if(a[0] >= a[max])
        {
            return 0;
        }
        
        return max;
        
    }


bool isIn(const double a1[], int n1, const double a2[], int n2)
    {
        if (n1 <= 0 && n2 > 0)
        {
            return false;
        }
        
        if (n2 <= 0)
        {
            return true;
        }
        
        
        if(a1[0] == a2[0])
        {
            return isIn(a1+1, n1-1, a2+1, n2-1);
        }
        
        return isIn(a1+1, n1-1, a2,n2);
    }
