x = [];
y = [];
D = 2;
n = 1;

while (n<200)
    y(n) = D*(1-cos(0.01*pi*(n)));
    x(n) = D*sin(0.01*pi*n)*cos(0.01*pi*n);
    n = n+1;
end

plot(y,x);