% open log file
fid = fopen('data.log', 'r');
uk = [];
e = [];
e_dot = [];

% read first line in log file
tline = fgetl(fid);
i = 1;
while ischar(tline)
    % conver to array 4x1
    numbers = textscan(tline, '%f', 'Delimiter', ',');
    numbers = numbers{1}; 
    % choose data 
    uk(i) = numbers(1,1);
    e(i) = numbers(2,1);
    e_dot(i) = numbers(3,1);
    i = i+1;
    % read next line in log file
    tline = fgetl(fid);
end
% close file
fclose(fid);
% creat axis time
sample_time = 0.01;
time = [];
num_sample = size (uk);
num_sample = num_sample(2);
time(1) = 0;
for j = 2:num_sample
   time(j) = (j-1)*sample_time;
end
%% fuzzy
figure()
plot(time,uk, 'k');
hold on
plot(time,e, 'r');
hold on
plot(time,e_dot, 'b');
legend('output uk', 'error', 'error dot')
xlabel('time [s]')
ylabel('value')
grid on
title("Result Fuzzy Controller")

