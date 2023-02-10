# Unreal-GI_Project-Team_WANTED

This is an UNREAL Project Repository, which is used for the "Game Interfaces" course.
The Project is about a Ball Game.

====================================================================================================================================================
HOW TO GET THE PROJECT RUNNING:

0) Projekt von GitHub in einen random ordner pullen
1) Rechtsklick auf BallGame Unreal Projekt und "Generate Visual Studio Project Files" auswählen.
2) BallGame.sln mit VS öffnen
3) Rechts im Projektmappen Editor rechtsklick auf BallGame(Im Ordner Games zu finden) und "als Startprojekt festlegen"
4) Danach wieder rechtsklick auf BallGame und "Erstellen" auswählen.
5) Wenn beim Builden ein Error kommt (ShootingTime blendet Klassenmember aus) dann zum Error navigieren und den Code umändern, dass er so aussieht: 

void AThrowingCharacter::ShootingStrengthUpdated(float ShootingTime1)
	{
		ThrowingCharacter_eventShootingStrengthUpdated_Parms Parms;
		Parms.ShootingTime=ShootingTime1;
		ProcessEvent(FindFunctionChecked(NAME_AThrowingCharacter_ShootingStrengthUpdated),&Parms);
	}

(Basically 2mal ShootingTime zu ShootingTime1 umbenennen, irgendwie wird das beim Pushen auf Github nie übernommen.

6) Speichern und nochmal "Erstellen" versuchen
7) Bei weiteren Errors Marlene fragen xd
8) War der Build erfolgreich kann das Projekt mit Doppelklick auf das BallGame Unreal Projekt gestartet werden. 