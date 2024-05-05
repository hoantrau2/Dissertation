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
%     if theta(n+1) <0
%         theta(n+1) = theta(n+1)+2*pi;
%     end
%     theta(n+1) = atan2(Y0-y(n+1), X0 - x(n+1));
    n = n+1;
end
theta = theta*180/pi;
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