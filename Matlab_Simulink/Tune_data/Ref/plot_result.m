% step = 0.3m, ee = 0.1 m, v = 0.2 m/s

% open log file
fid = fopen('data.log', 'r');
sample_time = 0.01;
x = [];
y = [];
x_ref = [];
y_ref = [];

angle_ref = [];
angle_robot = [];

% read first line in log file
tline = fgetl(fid);
i = 1;
while ischar(tline)
    % conver to array 4x1
    numbers = textscan(tline, '%f', 'Delimiter', ',');
    numbers = numbers{1}; 
    % choose data 
    x_ref(i) = numbers(1,1);
    y_ref(i) = numbers(2,1);
    x(i) = numbers(3,1);
    y(i) = numbers(4,1);
    angle_ref(i) = numbers(5,1)*180/pi;
    angle_robot(i) = numbers(6,1)*180/pi;
    i = i+1;
    % read next line in log file
    tline = fgetl(fid);
end
% close file
fclose(fid);

%% 
figure()
plot(y_ref,x_ref, 'r');
hold on
plot(y,x, 'k');
hold on
% plot(time,e_dot, 'b');
legend('ref', 'actual');
xlabel('y [m]')
ylabel('x [m]')
grid on
title("Result")

%% creat axis time
time = [];
num_sample = size (angle_ref);
num_sample = num_sample(2);
time(1) = 0;
for j = 2:num_sample
   time(j) = (j-1)*sample_time;
end
%%
figure()
plot(time,angle_ref, 'r');
hold on
plot(time,angle_robot, 'k');
hold on
legend('angle ref', 'angle robot angle');
xlabel('time [s]')
ylabel('theta [degree]')
grid on
title("Result angle")