PHI = pi/4;  %rad
D = 0.03; %m
numD = 70; 
sign = 1;
n = 2;
pre_nx = 1;
x = [];
y = [];
x(1) = D*cos(PHI);
y(1) = D*sin(PHI);
theta = [];
theta(1) = pi/4;


while(n<4*numD)
    y(n) = D*n*cos(PHI);
    nx = pre_nx + sign;
    x(n) = D*nx*sin(PHI);
    if (mod(n,numD) == 0 )
        sign = -sign;
    end
    theta(n) = atan2(y(n)-y(n-1),x(n)-x(n-1));
    pre_nx = nx;
    n = n+1;
end
% x(end) = [];
% y(end) = [];
theta = rad2deg(theta)
plot(y,x)