x = [];
y = [];
theta = [];
D = 1; % radius 1m
n = 2;
theta(1) = 0;
x(1) = 0;
y(1) = 0;

while (n<200)
    y(n) = D*(1-cos(0.01*pi*(n)));
    x(n) = D*sin(0.01*pi*n)*cos(0.01*pi*n);
    theta(n) = atan2(y(n)-y(n-1),x(n)-x(n-1));
    n = n+1;
end
theta = theta*180/pi;

% creat axis time
timed = [];
num_sample = size (x);
num_sample = num_sample(2);
timed(1) = 0;
for j = 2:num_sample
   timed(j) = (j-1)*0.1;
end
figure()
plot(timed,theta, 'r');
hold on
xlabel('time [s]')
ylabel('angle[degree]')
grid on
title("Referenced Planning Map")

%%%%%%%%%%%%%%%%%%%
figure()
plot(y,x)
xlabel('y [m]')
ylabel('x [m]')
grid on
title("Referenced Planning Map")