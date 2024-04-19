D = 0.5;
n = 1;
x = [];
y = [];

while (n<20)
    y(n) = D*n;
    x(n) = D*sin(0.1*pi*(n));
% x(n) = D*sin(y(n));
    n = n+1;
end

plot (y,x);