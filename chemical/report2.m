
function y=x(t)

  ## (1-1)
  ## r1= 8.66e+3
  ## r2= 1.11e+5
  ## r3= 1.11e+6
  ## r4= 2.44e+4
  ## (1-2)
  ## r1= 3.45e+3
  ## r2= 4.43e+4
  ## r3= 4.43e+5
  ## r4= 3.88e+3
  ## (1-3)
  r1= 1.95e+2
  r2= 2.58e+3
  r3= 2.68e+4
  r4= 0.0
	 

  A=[-r1-r4, r2, r3;...
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
