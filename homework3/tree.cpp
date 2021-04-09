int countIsIn(const double a1[], int n1, const double a2[], int n2)
    {
        if(n1 < 0)
        {
            return 0;
        }
        
        if(n2 <= 0)
        {
            return 0;
        }
        
        if(n1 == 1 && n2 ==1 && a1[0] == a2[0])
        {
            return 1;
        }
        
        if(n1 == 1 && n2 > 1)
        {
            return 0;
        }
        
        if(a1[0] == a2[0])
        {
            return countIsIn(a1+1, n1-1, a2+1, n2-1);
        }
        
        return countIsIn(a1+1, n1-1, a2, n2);
    }



void exchange(double& x, double& y)
    {
        double t = x;
        x = y;
        y = t;
    }

void divide(double a[], int n, double divider,
                        int& firstNotGreater, int& firstLess)
    {
        if (n < 0)
            n = 0;

        firstNotGreater = 0;
        firstLess = n;
        int firstUnknown = 0;
        while (firstUnknown < firstLess)
        {
            if (a[firstUnknown] < divider)
            {
                firstLess--;
                exchange(a[firstUnknown], a[firstLess]);
            }
            else
            {
                if (a[firstUnknown] > divider)
                {
                    exchange(a[firstNotGreater], a[firstUnknown]);
                    firstNotGreater++;
                }
                    firstUnknown++;
            }
        }
    }

    void order(double a[], int n)
    {
        if(n <=1)
        {
            return;
        }
        int x, y;
        
        divide(a, n, a[n/2], x, y);
        
        order(a, x);
        
        order(a+y, n-x);
    }
