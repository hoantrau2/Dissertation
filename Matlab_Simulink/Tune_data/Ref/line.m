A = 0.577;
B = 0;
STEP = 0.10; %10cm
X_MAX = 5; % 5m

x = [];
y = [];
theta = [];
x(1) = 0;
y(1) = 0;
theta(1) = atan2(A,1);
i = 1;

while (x <= X_MAX)
    i = i+1;
    x(i) = x(i-1) + STEP;
    y(i) = A*x(i)+B;
    theta(i) = atan2(y(i)-y(i-1),x(i)-x(i-1));
end
theta = rad2deg(theta);
plot(y,x)