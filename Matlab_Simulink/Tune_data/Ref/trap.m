
a = 0.5;
b = 1.5;
c = 2.5;
d = 3.5;
x = [];
y =[];
theta = [];
STEP = 0.01;
COUNTER = 4.5/STEP +1
x(1) = 0;
y(1) = 0;

for i = 2:COUNTER
 x(i) = x(i-1)+STEP;
    if (x(i) <= a) 
        y(i) = 0;
    elseif ((x(i) >= a) && (x(i) <= b)) 
        if (a == b) 
            y(i) = 1;
        else 
            y(i) = (x(i) - a) / (b - a);
        end
    elseif ((x(i) >= b) && (x(i) <= c)) 
        y(i) = 1;
    elseif ((x(i) >= c) && (x(i) <= d)) 
        if (c == d) 
            y(i) = 1;
        else
            y(i) = (d - x(i)) / (d - c);
        end
    else
        y(i) = 0;
    end
    theta(i) = atan2(y(i)-y(i-1),x(i)-x(i-1));

end
theta= theta*180/pi;
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