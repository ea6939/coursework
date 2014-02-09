


group1 = wavread('DSPLabG1.wav');

T1 = length(group1);
fs = 10000;

group1f = fft(group1);

t = 1:length(group1);
f = t*fs/(length(t));
time = 0: 2119;

%apply noise suppression filter designed using SP Toolbox
group1_clean = filter(IIR_butterworth_1450_1650, group1);

subplot(2,1,1), plot(group1);
title('Noisy signal');
axis([0 2200 -5 15]);

subplot(2,1,2), plot(time, group1_clean);
%title('Signal after noise suppression with FIR LPF - Fpass 1550 and Fstop 1650 Hz');
title('Signal after noise suppression with IIR LPF - Fpass 1450 and Fstop 1650 Hz');
axis([0 2200 -2 4]);