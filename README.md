# stressvogel

De gamelogica en het entry point van ons spel.

![Preview](preview.jpg)

1. Open Eclipse.
2. Maak een BSP aan met de sopcinfo van de Media Computer of onze computer.
3. Ga naar `File -> Import -> Git -> Projects from Git -> Clone URI`
4. Geef de locatie (HTTPS of SSH adres) van de Stressvogel repo op (NIET VAN DE SUBMODULE REPOS)
5. Belangrijk: vink "clone submodules" aan wanneer het gevraagd wordt. Als je dit hokje niet aanvinkt dan komen de `library/ral/` en `library/ial/` submodule contents niet mee.
6. Wanneer de project is geimporteerd en je deze probeert te builden komt er een error dat de BSP niet bestaat. Ga naar de `Project Properties -> Nios II Properties` en kies het pad naar de BSP die je in Stap 1 had aangemaakt in het `BSP Project Location` veld.
7. Voeg aan je persoonlijke makefile de compiler option `-std=c++17` toe.
8. Kaif.

