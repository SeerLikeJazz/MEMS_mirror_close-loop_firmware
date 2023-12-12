clear;clc
fs = 16000; % 采样率
% t = 0:1/fs:1-1/fs; % 时间范围
t = 0:1/fs:0.01-1/fs; % 时间范围

% 生成信号1和信号2（频率相同，相位差为30度）
f = 462; % 频率
phase_diff_deg = 30; % 相位差（度）
phase_diff_rad = deg2rad(phase_diff_deg); % 将度转换为弧度

signal1 = 2*sin(2*pi*f*t); % 信号1
signal2 = sin(2*pi*f*t + phase_diff_rad)+12; % 信号2，加上相位差

% 显示信号1和信号2的波形
figure;
subplot(2,1,1);
plot(t, signal1);
title('Signal 1');
xlabel('Time');
ylabel('Amplitude');

subplot(2,1,2);
plot(t, signal2);
title('Signal 2');
xlabel('Time');
ylabel('Amplitude');

%%%%%%%%%%%%%
% 计算信号1和信号2的互相关函数
[acor, lag] = xcorr(normalize(signal1), normalize(signal2));

% 找到互相关函数的最大值及其位置
[~, idx] = max(abs(acor)); % 找到绝对值最大值
lagDiff = lag(idx); % 获取相应的位置（时延）

% 将时延转换为相位差（假设采样频率为fs）
timeDiff = lagDiff / fs; % 转换为时间差
phaseDiff_rad = timeDiff * 2*pi*f; % 将时间差转换为相位差（弧度）
phaseDiff_deg = rad2deg(phaseDiff_rad); % 将弧度转换为度数

fprintf('Estimated phase difference: %f degrees\n', phaseDiff_deg);