% IIR + FIR %
function y = antimetal(x, FIR, IIR)

y = conv(x,IIR);
y = conv(y,FIR);

