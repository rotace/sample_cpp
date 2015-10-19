
function y=x(t)

  r1= 2.3e+3
  r2= 1.8e+4
  r3= 9.7e+4

  A=[-r1, r2, r3;...
      r1,-r2,0  ;...
      r1, r2,-r3]

  rank(A)

  l=eig(A)

  [V,LAMBDA] = eig(A)

  x0= 0
  y0= 0
  z0= 1.22e-16

  xo=[x0,y0,z0]'

  a= inv(V)*xo

  y=diag([exp(l(1)*t), exp(l(2)*t), exp(l(3)*t)])*V*a;
  
endfunction


x(1e-5)
disp('end')