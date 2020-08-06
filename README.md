# 42_RTv1

### Raytracing program for rendering computer-generated images. 

___Usage___

>./RTv1 scenes/[file]

___Making a scene___

1. Create a file in "scenes" directory

2. There _must_ be at least: 1 object, 1 camera, 1 light source

### Objects

type x,y,z,Vx,Vy,Vz,angle,r,specular,color

_type: sphere/cone/cylinder/plane_
 
_coordinates of a center (or a point on a plane): x, y, z_

_normal's coordinates: Vx, Vy, Vz_

_angle must be between 0 and 1 to work properly_
 
_r: radius_
 
_color: red/green/blue/yellow/aqua/gray/grey/grey1_

### Light

light type x,y,z,intensity

_type: point/direction_

## Camera

camera canv_h,canv_w,canv_d,x,y,z,rot_x,rot_y,rot_z

*canv_h, canv_w, canv_d preferably set to 960*

*rot_x, rot_y, rot_z are angles at which you rotate x, y, z axis*

## Ambient

Ambience is a background lighting, it must be a number from 0 to 1 to work properly

## ___Sphere___

Vx, Vy, Vz, angle must be 0

## ___Cone___

r must be 0

## ___Cylinder___

Angle must be 0

## ___Plane___

r and angle must be 0

