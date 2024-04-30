R = 1; % m
X0 = 0; % m
Y0 = R; %m
PHI = pi/180; % 1 degree
n_max = (2*pi)/PHI;
n = 0;
x = [];
y = [];
theta = [];

while (n<=n_max)
    y(n+1) = Y0 - R*(cos(n*PHI));
    x(n+1) = X0 + R*(sin(n*PHI));
    theta(n+1) = atan2(Y0-y(n+1), X0 - x(n+1))-pi/2;
    n = n+1;
end
theta = theta*180/pi;
 plot(y,x)