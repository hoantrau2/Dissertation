PHI = pi/6;
X0 = 1;
Y0 = 1;
R = 2;

max_n = (2*pi/PHI);

x = [];
y = [];

for n = 0: max_n
    x(n+1) = X0+R*(1-cos(n*PHI));
    y(n+1) = Y0+R*(1+sin(n*PHI));
end

plot(x,y)
    
