R = 1; % m
X0 = -R; % m
Y0 = 0; %m
PHI = pi/180; % 1 degree
n_max = (2*pi)/PHI;
n = 0;
x = [];
y = [];
while (n<=n_max)
    y(n+1) = Y0 + R*(1-cos(n*PHI));
    x(n+1) = X0 + R*(1+sin(n*PHI));
    n = n+1;
end
 plot(y,x)