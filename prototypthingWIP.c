//System 1

main()
{
	if(encoder.button == 1)
		ButtonSelect()
		
			
			
}

void ButtonSelect() // Väljer fönster när knapp trycks
{
	
	if (fönster == 0) && (knapp == 0) // Fönster är 0 knappval 0 -> UndreGräns fönster
		fönster = 1; 
	if (fönster == 0) && (knapp == 1) // Fönster är 0 knappval 1 -> ÖvreGräns fönster
		fönster = 2; 
	if (fönster == 1) || (fönster == 2) // går tillbaka till 0
		fönster = 0;
}

void MenuSystem(int direction) //Väljer knapp i fönster eller ändrar övre/undreGräns beroende på fönster)
{
	if (fönster == 0)//Om du är i fönstrer 0, fönster har 2 två knappval, 
		{ 
			knapp+=direction;
			if(knapp == maxknapplength) //
				knapp = 0
		}
		if (fönster == 1) //fönster 1 =  kan ändra övreGräns 
		{
			ÖvreGränsParameter += direction
		}
		if(fönster == 2)//fönster 2 -> kan ändra undreGräns
		{
			UndreGränsParameter+= direction
		}
	
}
