void Boilerio_sildymas(){
  #ifdef DEBUGboileris
  if (Bo_sSiurblys == true) Serial.println("Boilerio siublio busena: IJUNGTAS *** ON ***");
    if (Bo_Siurblys == false) Serial.println("Boilerio siublio busena: ISUNGTAS *** OFF ***");
  #endif 

// Jei  boilerio viršus šaltesnis už boilerio šildymo išjungimo temperatūrą, 
// o katilo išėjime yra daugiau šilumos, negu nustatyta boilerio šildymo pradžios  
// temperatūra +10 C, tai įjungiamas boilerio siurblys
     if ((BoTop < config.b_ON_T || BoTop < config.b_OFF_T) && KaOut > config.b_ON_T + 10 && config.Bo_Siurblio_busena == false){
       if (KaOut > BoTop + 10){
       digitalWrite(BoSiurblys, LOW); 
       config.Bo_Siurblio_busena = true;
#ifdef DEBUGboileris
Serial.println("Boilerio siublys IJUNGTAS ***_ON_ ***__PRIEZASTIS:");
Serial.print("B isjungimo temperatura- ");Serial.print(config.b_OFF_T);Serial.print(char(186));Serial.println("C");
Serial.print("B ijungimo temperatura- ");Serial.print(config.b_ON_T);Serial.print(char(186));Serial.println("C");
Serial.print("I isejime temperatura- ");Serial.print(KaOut);Serial.print(char(186));Serial.println("C");
#endif 
   }}
// Jei boilerio viršuje yra tiek šilumos, kiek nustatyta, arba katilo išėjime yra mažiau šilumos, 
// negu boilerio viršuje, tai siurblys išjungiamas
     if ((BoTop >= config.b_OFF_T || KaOut <= BoTop + 8) && (config.Bo_Siurblio_busena == true)) { 
       digitalWrite(BoSiurblys, HIGH); 
       config.Bo_Siurblio_busena = false;
#ifdef DEBUGboileris
Serial.println("Boilerio siublys ISUNGTAS ***_OFF_***__PRIEZASTIS:");
Serial.print("B isjungimo temperatura- ");Serial.print(config.b_OFF_T);Serial.print(char(186));Serial.println("C");
Serial.print("B ijungimo temperatura- ");oerial.print(config.b_ON_T);Serial.print(char(186));Serial.println("C");
Serial.print("I isejime temperatura- ");Serial.print(KaOut);Serial.print(char(186));Serial.println("C");
#endif      
   }     
}

//**************************************************************************************************************
void Boilerio_termostatas(){
// Jei boilerio viršus šaltesnis negu nustatyta ijungimo temperatura, arba boilerio viršus šaltesnis
// už boilerio išjungimo temperatūrą, ir ijungtas termostatas, tai jungiamas elektrinis boilerio sildymas
if ((BoTop < config.b_ON_T ) && (config.Bo_Termostatas_ON == true)){
       digitalWrite(BoTermostatas, LOW); 
       config.Bo_Termostato_busena = true; // zyme, kad termostatas dabar veikia
//     B_Termostatas_ON = false;    // kai ijungiamas elektrinis boilerio sildymas, pakeiciama ijungimo zyme
#ifdef DEBUGboileris
Serial.print("Boilerio sildymas elektra I_J_U_N_G_T_A_S ***_ON_ *** iki- "); 
Serial.print(config.b_OFF_T);Serial.print(char(186));Serial.println("C");
Serial.println();
#endif 
   }
// Jei boilerio virsuje yra tiek šilumos, kiek nustatyta,  tai termostatas isjungia boilerio sildyma elektra
     if ((BoTop >= config.b_OFF_T)  && (config.Bo_Termostato_busena == true)) { 
       digitalWrite(BoTermostatas, HIGH);
       config.Bo_Termostato_busena = false;
#ifdef DEBUGboileris
Serial.println("Ijungtas boilerio sildymas elektra I*S*J*U*N*G*T*A*S ***_OFF_ *** nuo- ");
Serial.print(BoTop);Serial.print(char(186));Serial.println("C");
#endif      
   }     
}
