A = 1;
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
%%%%%%%%%%%%%%%%%%%
figure()
plot(y,x)
xlabel('y [m]')
ylabel('x [m]')
grid on
title("Referenced Planning Map")
%%%%%%%%%%%%%%%%%%%%
% creat axis time
timed = [];
sample_time = 0.1;
num_sample = size (x);
num_sample = num_sample(2);
timed(1) = 0;
for j = 2:num_sample
   timed(j) = (j-1)*sample_time;
end
figure()
plot(timed,theta, 'r');
hold on
xlabel('time [s]')
ylabel('angle[degree]')
grid on
title("Referenced Planning Map")