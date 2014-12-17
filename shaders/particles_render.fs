#version 410                                                                       
                                                                                    
uniform sampler2D color_map;                                                        
                                                                                    
in vec2 TexCoord;                                                                   
out vec4 FragColor;                                                                 
                                                                                    
void main()                                                                         
{                                                                                   
    FragColor = texture2D(color_map, TexCoord);                                     
                                                                                    
    if (FragColor.r >= 0.5 && FragColor.g >= 0.5 && FragColor.b >= 0.5) {           
        discard;                                                                    
    }                                                                               
}
