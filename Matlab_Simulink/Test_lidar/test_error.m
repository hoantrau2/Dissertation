% open log file
fid = fopen('data1.log', 'r');
x = [];
y = [];
x_ref=[];
y_ref=[];

% read first line in log file
tline = fgetl(fid);
i = 1;
sample_time = 0.2;
while ischar(tline)
%     conver to array 4x1
    numbers = textscan(tline, '%f', 'Delimiter', ',');
    numbers = numbers{1}; 
%     choose data 
    
    x(i) = numbers(1,1);
    y(i) = numbers(2,1);
       i = i+1;
    % read next line in log file
    tline = fgetl(fid);
end
% creat axis time
timee = [];
num_sample = size (x);
num_sample = num_sample(2);
timee(1) = 0;
x_ref(1) = 0;
y_ref(1) = 0;
for j = 2:num_sample
   timee(j) = (j-1)*sample_time;
   x_ref(j) = 0;
   y_ref(j) = 0;
end
%%%%%%%%%%%
figure()
plot(timee,x, 'k');
hold on
plot(timee,x_ref, 'b');
hold on
xlabel('time [s]')
ylabel('x [m]')
grid on
title("Data axis X Lidar")
%%%%%%%%%%%
figure()
plot(timee,y, 'k');
hold on
plot(timee,y_ref, 'b');
hold on
xlabel('time [s]')
ylabel('y [m]')
grid on
title("Data axis Y Lidar")
