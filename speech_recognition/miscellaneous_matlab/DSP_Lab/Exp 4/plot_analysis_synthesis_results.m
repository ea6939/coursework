% plot of test signal vs analysis synthesis

reconstructor;

subplot(2,1,1), plot(test_signal);
axis([0 1450 -1.5 1.5])
subplot(2,1,2), plot(Xhat);
axis([0 1450 -1.5 1.5])