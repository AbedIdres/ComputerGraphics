## Light Types

### Ambient

<img src="./pictures/ySQoNUgzr9.png" width="400">  <img src="./pictures/tex7Lmd8qn.png" width="400">





Here we demonstrate the ambient light,  it works by multiplying the  ambient colors of light and model, because it work  the same way on point and parallel light it will show the same behavior.

### Diffuse 

#### Parallel light

 <img src="./pictures/MeshViewer_sZsHQfe460.png" width="400"> <img src="./pictures/MeshViewer_e2mNkoyxGg.png" width="400">





Diffuse color with Parallel light. We can see that the light is in the shape of an arrow indicating the direction of the light. The direction is the normal of the plane which created by the parallel light source. Applying translate transformation on the light source does not change the direction of the light, and thus no changes on the sphere. The  light should always cover half of the sphere.

#### Point light

 <img src="./pictures/MeshViewer_Pn90Td6QYD.png" width="400"> <img src="./pictures/MeshViewer_nQ2sLcmsLB.png" width="400">  

Diffuse color with point light. We can that the light is in the shape of a sphere because the light emits lights in every direction. We can see that whenever we translate the point lights source the sphere color changes,  but whenever we rotate the point light source the colors remain the same.

### Specular

#### Parallel light

<img src="./pictures/Zoom_4nBKdPWjrw.png" width="400">

Here we have the specular light with a parallel light .

#### Point light

<img src="./pictures/Zoom_P3ivz8da89.png" width="400">

Here we have the point light with a parallel light .

## Materials

<img src="./pictures/MeshViewer_K8DUKfJsFG.png" width="400">

We gave the user the options to choose material colors for the model.

## Shading types

### Flat

<img src="./pictures/chrome_XnE0uymuoY.png" width="400"> <img src="./pictures/MeshViewer_UXbjyaTIQ4.png" width="400">

We use the triangle center to color the the faces and use tringle centers to calculate colors,



### Gouraud

<img src="./pictures/chrome_exOlLbCEvz.png" width="400"> <img src="./pictures/MeshViewer_NT55zZkXbr.png" width="400">

We interpolate on the face using  three colors calculated using  three varices constructing the face and using normals per vertex per face.

### Phong

<img src="./pictures/chrome_TPTkFEEOrB.png" width="400"> <img src="./pictures/MeshViewer_896vIyibtE.png" width="400">

We interpolate nomrals of the three vertices constructing the face,and then we calculate the normal for each point on tringle and calculate color using new normal.

## Demonstration

### It's Over 9000!

<img src="./pictures/‏‏furious beethoven.png" width="400"> <img src="./pictures/1584452342_Dragon-Ball-Z-Kakarot-will-receive-Goku-and-Vegeta-Super-1024x576.jpg" width="400">



Super Saiyan  God Beethoven evolves into Pikachu . we used specular with diffuse and a little spice of ambient for Beethoven  and for the bananas we used only diffuse and ambient light because banana is not specular although its spectacular .

### Power of a million faces

<img src="./pictures/WhatsApp Image 2021-01-12 at 19.22.13.jpeg" width="400">

specular and diffuse light used to display this monster of computation complexity.



### Simple is beautiful

<img src="./pictures/WhatsApp Image 2021-01-12 at 19.35.04.jpeg" width="400"> <img src="./pictures/WhatsApp Image 2021-01-12 at 19.35.20.jpeg" width="400">

specular and diffuse light used, when you just want a cup of tea but there is only tea and no cup.

### Animals at the disco 

<img src="./pictures/WhatsApp Image 2021-01-12 at 19.51.58.jpeg" width="400"> <img src="./pictures/WhatsApp Image 2021-01-12 at 19.57.41.jpeg" width="400">

background color change with diffuse and specular light, sphere and cow is in flat shading, dolphin is in Gouraud shading and bunny is in phong shading, on the right we have fog effect. Time to boogie like its 1969. 

### Beethoven new mix cover art

<img src="./pictures/WhatsApp Image 2021-01-12 at 21.09.26.jpeg" width="400"> <img src="./pictures/WhatsApp Image 2021-01-12 at 21.10.52.jpeg" width="400">

diffuse lighting with background color change, we can see Beethoven behind the scenes getting ready to drop his new sick mixtape, Symphony No. 10, soon available on Spotify and Apple music,  get your copy soon.  

### Someday I'm gonna be a real boy`

<img src="./pictures/WhatsApp Image 2021-01-16 at 22.54.29.jpeg" width="800">

diffuse,speculate  ambient , texture , everything you want...

He sees you when you're sleeping,He knows when you're awake,He knows if you've been bad or good,So be good for goodness sake! 

### Multiple lights source

<img src="./pictures/Zoom_pEusxGkyKP.png" width="400"><img src="./pictures/WhatsApp Image 2021-01-10 at 15.03.57.jpeg" width="400"> 



we show multiple light using parallel light.

## Post Processing Effects

### Bloom + Gaussian Blur

 <img src="./pictures/Zoom_8YYjAjRlhk.png" width="400">  <img src="./pictures/Zoom_aL5T606hhl.png" width="400">  

We allow the user to choose the threshold. Lower threshold means more ✨shinny✨ objects. source image on the left bloom effect on the right.

### Fog Effect

 <img src="./pictures/MeshViewer_qa0ou7Zr7g.png" width="400">

Here we can see the original pictures.

#### Linear

<img src="./pictures/MeshViewer_dU2hfdfDkd.png" width="400">

Users can choose the start and end of fog effect.

#### Exponential 

<img src="./pictures/MeshViewer_Z0RK3MSzTu.png" width="400">

Users can choose density of the fog.

#### Exponential Squared 

<img src="./pictures/dMtPScq6K3.png" width="400">

Users can choose density of the fog.

### Procedural textures 

<img src="./pictures/proceduralTexture .png" width="400">

We give the user the option to choose the intensity factor for the procedural textures.





## Thanks for watching folks and good night