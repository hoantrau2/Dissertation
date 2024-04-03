% M? file log
fid = fopen('client.txt', 'r');
v1 = [];
v2 = [];
v3 = [];
v4 = [];
% ??c t?ng dòng trong file log
tline = fgetl(fid);
i = 1;
while ischar(tline)
    % Phân tách dòng thành các s? float
    numbers = textscan(tline, '%f', 'Delimiter', ',');
    numbers = numbers{1} % L?y m?ng s? float t? cell array
    v1(i) = numbers(1,1);
    v2(i) = numbers(2,1);
    v3(i) = numbers(2,1);
    v4(i) = numbers(4,1);
    i = i+1;
    % ??c dòng ti?p theo trong file
    tline = fgetl(fid);
end
% ?óng file
fclose(fid);

sample_time = 0.01;
time = [];
num_sample = size (v1);
num_sample = num_sample(2);
time(1) = 0;

vl_ref = ones(1, num_sample) * 0.5;
vr_ref = ones(1, num_sample) * 0.5;


for j = 2:num_sample
   time(j) = (j-1)*sample_time;
end

% %% motor 1
figure()
plot(time,v1, 'k');
hold on
plot(time,vl_ref, 'r');
legend('v real, v ref')
xlabel('[m/s]')
ylabel('[m/s]')
grid on
title("Velocity motor 1")

