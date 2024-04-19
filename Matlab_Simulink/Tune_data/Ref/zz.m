PHI = pi/4;  %rad
D = 0.5; %m
sign = 1;
n = 1;
pre_nx = 0;
x = [];
y = [];
while(n<21)
    y(n) = D*n*cos(PHI);
    nx = pre_nx + sign;
    x(n) = D*nx*sin(PHI);
    if (mod(n,4) == 0 )
        sign = -sign;
    end
    pre_nx = nx;
    n = n+1;
end
plot(y,x)