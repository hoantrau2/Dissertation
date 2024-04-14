% open log file
fid = fopen('data_fuzzy.log', 'r');
sample_time = 0.01;
Ke = 0.159;
uk = [];
e = [];
e_dot = [];
setpoint = [];
angle = [];

% read first line in log file
tline = fgetl(fid);
i = 1;
while ischar(tline)
    % conver to array 4x1
    numbers = textscan(tline, '%f', 'Delimiter', ',');
    numbers = numbers{1}; 
    % choose data 
    setpoint(i) = numbers(3,1);
    uk(i) = numbers(4,1);
    e(i) = numbers(5,1);
    e_dot (i) = numbers(6,1);
    i = i+1;
    % read next line in log file
    tline = fgetl(fid);
end
% close file
fclose(fid);

% cal current angle
angle = setpoint-(e/Ke)*180/pi;
% creat axis time
time = [];
num_sample = size (uk);
num_sample = num_sample(2);
time(1) = 0;
for j = 2:num_sample
   time(j) = (j-1)*sample_time;
end
%% fuzzy
figure()
plot(time,setpoint, 'r');
hold on
plot(time,angle, 'k');
hold on
% plot(time,e_dot, 'b');
legend('setpoint', 'current angle');
xlabel('time [s]')
ylabel('theta [degree]')
grid on
title("Result Fuzzy Controller")

figure()
plot(time,e, 'r');
hold on
plot(time,e_dot, 'k');
hold on
plot(time,uk, 'b');
legend('error','e dot','control signal');
xlabel('time [s]')
ylabel('value')
grid on
title("Input and Output of Fuzzy Controller");