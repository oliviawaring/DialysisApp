void storeData ()
{
   var wrblock[256]; // 512 bytes to be written into a uSD card
   media_SetSector(0,10); // I really don't know how this works and I'm honestly quite afraid now
   // how do I name this variable? how do I access it later? Why is everything so challenging?
   if (media_WrSector(wrblock))
      Serial.print("success!");
}

void loadData () 
{
   var wrblock[256]; // 512 bytes to be read from a uSD card
   media_SetSector(0,10); // I really don't know how this works and I'm honestly quite afraid now
   if (media_RdSector(rdblock))
      Serial.print("success!");
}

