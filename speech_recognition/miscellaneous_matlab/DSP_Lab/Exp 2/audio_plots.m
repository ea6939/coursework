

clean = wavread('CleanSig.wav');
noisy = wavread('NoisySig.wav');
group1 = wavread('DSPLabG1.wav');

subplot(3,1,1), plot(clean);
title('Clean Signal');
subplot(3,1,2), plot(noisy);
title('Noisy Signal');
subplot(3,1,3), plot(group1);
title('Group 1');
axis([0 2200 -20 20]);