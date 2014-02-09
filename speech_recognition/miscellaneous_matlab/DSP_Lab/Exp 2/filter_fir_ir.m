

filter_ir = zeros(1000, 1);
filter_ir(1) = 1;

imp_resp = filter(LPF1550_1650, filter_ir);

plot(imp_resp);


