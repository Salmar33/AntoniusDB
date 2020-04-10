#ifndef DEFAULTMEASURES_H
#define DEFAULTMEASURES_H

#define DEFAULT_FONT_SIZE	12
#define BUFFER_SIZE			1000

#define SUCCESS				0
#define FAILURE				1

#define ABONNENTEN_SUCHE_CLICK_COLUMN	0

#define DATABASE_DATETIME_FORMAT		"yyyy-MM-dd HH:mm:ss"
#define DATABASE_DATE_FORMAT			"yyyy-MM-dd"
#define ANMERKUNGEN_DATE_FORMAT			"dd.MM.yyyy"

#define ZERO_DATETIME_STRING			"0000-00-00 00:00:00"

#define DATETIME_SPECIAL_VALUE			" "

//tab indices for the main tab widget
#define ABONNENTEN_TAB					0
#define ABONNENTEN_SUCHE_TAB			1

/** we make it custom to:
 *  .) always have the primary key (if it is the only key) of a table occupying the first column
 *  .) always have the content for combo boxes in the second column in its corresponding table
 */
#define ID_POS					0
#define COMBO_BOX_CONTENT_POS	1

/**********************************************************************/
//tables
#define ABONNENTEN_TABLE		QString("abonnentent")
#define ANREDE_TABLE			QString("anredet")
#define AMTSTITEL_TABLE			QString("amtstitelt")
#define STATUS_TABLE			QString("statust")
#define PLZ_TABLE				QString("plzaustriat")
#define ORT_TABLE				QString("ortaustriat")
#define PLZ_ORT_JUNC_TABLE		QString("plztoortaustriajunct")
#define BUCHUNGEN_TABLE			QString("buchungent")

/**********************************************************************/
//columns of ABONNENTEN_TABLE
#define ABONNENTEN_ID					QString("ID")
#define ABONNENTEN_ANREDE				QString("Anrede")
#define ABONNENTEN_TITELVOR				QString("TitelVorgestellt")
#define ABONNENTEN_TITELNACH			QString("TitelNachgestellt")
#define ABONNENTEN_AMTSTITEL			QString("Amtstitel")
#define ABONNENTEN_NACHNAME				QString("Nachname")
#define ABONNENTEN_VORNAME				QString("Vorname")
#define ABONNENTEN_ORGANISATION			QString("Organisation")
#define ABONNENTEN_STRASSE				QString("Straße")
#define ABONNENTEN_LAND					QString("Land")
#define ABONNENTEN_PLZAUSTRIA			QString("PLZaustria")
#define ABONNENTEN_ORTAUSTRIA			QString("Ortaustria")
#define ABONNENTEN_PLZALLGEMEIN			QString("PLZallgemein")
#define ABONNENTEN_ORTALLGEMEIN			QString("Ortallgemein")
#define ABONNENTEN_ANTONIUSANZAHL		QString("Antoniusanzahl")
#define ABONNENTEN_TELNR				QString("TelNr")
#define ABONNENTEN_MOBIL				QString("Mobil")
#define ABONNENTEN_EMAIL				QString("EMail")
#define ABONNENTEN_STATUS				QString("Status")
#define ABONNENTEN_ANMERKUNGEN			QString("Anmerkungen")
#define ABONNENTEN_DANKSCHREIBEN		QString("Dankschreiben")
#define ABONNENTEN_LETZTEAENDERUNG		QString("letzteÄnderung")
#define ABONNENTEN_ZUSATZINFO			QString("Zusatzinformation")
#define ABONNENTEN_ERSTELLTAM			QString("erstelltAm")
#define ABONNENTEN_STATUSGESETZTAM		QString("StatusGesetztAm")
#define ABONNENTEN_BERUFTAETIGKEIT		QString("BerufTätigkeit")
#define ABONNENTEN_MIETCODE				QString("Mietcode")

//positions of ABONNENTEN_TABLE
#define ABONNENTEN_ID_POS					0
#define ABONNENTEN_ANREDE_POS				1
#define ABONNENTEN_TITELVOR_POS				2
#define ABONNENTEN_TITELNACH_POS			3
#define ABONNENTEN_AMTSTITEL_POS			4
#define ABONNENTEN_NACHNAME_POS				5
#define ABONNENTEN_VORNAME_POS				6
#define ABONNENTEN_ORGANISATION_POS			7
#define ABONNENTEN_STRASSE_POS				8
#define ABONNENTEN_LAND_POS					9
#define ABONNENTEN_PLZAUSTRIA_POS			10
#define ABONNENTEN_ORTAUSTRIA_POS			11
#define ABONNENTEN_PLZALLGEMEIN_POS			12
#define ABONNENTEN_ORTALLGEMEIN_POS			13
#define ABONNENTEN_ANTONIUSANZAHL_POS		14
#define ABONNENTEN_TELNR_POS				15
#define ABONNENTEN_MOBIL_POS				16
#define ABONNENTEN_EMAIL_POS				17
#define ABONNENTEN_STATUS_POS				18
#define ABONNENTEN_ANMERKUNGEN_POS			19
#define ABONNENTEN_DANKSCHREIBEN_POS		20
#define ABONNENTEN_LETZTEAENDERUNG_POS		21
#define ABONNENTEN_ZUSATZINFO_POS			22
#define ABONNENTEN_ERSTELLTAM_POS			23
#define ABONNENTEN_STATUSGESETZTAM_POS		24
#define ABONNENTEN_BERUFTAETIGKEIT_POS		25
#define ABONNENTEN_MIETCODE_POS				26

/**********************************************************************/
//columns of ANREDE_TABLE
#define ANREDE_ID						QString("ID")
#define ANREDE_ANREDE					QString("Anrede")

//positions of ANREDE_TABLE
#define ANREDE_ID_POS						0
#define ANREDE_ANREDE_POS					1

/**********************************************************************/
//columns of AMTSTITEL_TABLE
#define AMTSTITEL_ID					QString("ID")
#define AMTSTITEL_AMTSTITEL				QString("Amtstitel")

//positions of AMTSTITEL_TABLE
#define AMTSTITEL_ID_POS					0
#define AMTSTITEL_AMTSTITEL_POS				1

/**********************************************************************/
//columns of STATUS_TABLE
#define STATUS_ID						QString("ID")
#define STATUS_STATUS					QString("Status")

//positions of STATUS_TABLE
#define STATUS_ID_POS						0
#define STATUS_STATUS_POS					1

/**********************************************************************/
//columns of PLZ_TABLE
#define PLZ_ID							QString("ID")
#define PLZ_PLZ							QString("PLZ")

//positions of PLZ_TABLE
#define PLZ_ID_POS							0
#define PLZ_PLZ_POS							1

/**********************************************************************/
//columns of ORT_TABLE
#define ORT_ID							QString("ID")
#define ORT_ORT							QString("Ort")

//positions of ORT_TABLE
#define ORT_ID_POS							0
#define ORT_ORT_POS							1

/**********************************************************************/
//columns of BUCHUNGEN_TABLE
#define BUCHUNGEN_ID					QString("BuchungsID")
#define BUCHUNGEN_UEBERWEISER_ID		QString("ÜberweiserID")
#define BUCHUNGEN_BUCHUNGSNUMMER		QString("Buchungsnummer")
#define BUCHUNGEN_IBAN					QString("IBAN")
#define BUCHUNGEN_BIC					QString("BIC")
#define BUCHUNGEN_DATUM					QString("Datum")
#define BUCHUNGEN_STATUS				QString("Status")
#define BUCHUNGEN_GEGKTO				QString("GegKto")
#define BUCHUNGEN_VERWENDUNGSZWECK		QString("Verwendungszweck")
#define BUCHUNGEN_BETRAG				QString("Betrag")
#define BUCHUNGEN_EINGEHEND				QString("Eingehend")
#define BUCHUNGEN_DANKBRIEF				QString("Dankbrief")
#define BUCHUNGEN_LETZTE_AENDERUNG		QString("letzteÄnderung")

//positions of BUCHUNGEN_TABLE
#define BUCHUNGEN_ID_POS                    0
#define BUCHUNGEN_UEBERWEISER_ID_POS		1
#define BUCHUNGEN_BUCHUNGSNUMMER_POS		2
#define BUCHUNGEN_IBAN_POS					3
#define BUCHUNGEN_BIC_POS					4
#define BUCHUNGEN_DATUM_POS					5
#define BUCHUNGEN_STATUS_POS				6
#define BUCHUNGEN_GEGKTO_POS				7
#define BUCHUNGEN_VERWENDUNGSZWECK_POS		8
#define BUCHUNGEN_BETRAG_POS				9
#define BUCHUNGEN_EINGEHEND_POS				10
#define BUCHUNGEN_DANKBRIEF_POS				11
#define BUCHUNGEN_LETZTE_AENDERUNG_POS		12

/**********************************************************************/
//columns of PLZ_ORT_JUNC_TABLE
#define PLZ_ORT_JUNC_PLZ_ID				QString("PLZID")
#define PLZ_ORT_JUNC_ORT_ID				QString("OrtID")

//positions of PLZ_ORT_JUNC_TABLE
#define PLZ_ORT_JUNC_PLZ_ID_POS				0
#define PLZ_ORT_JUNC_ORT_ID_POS				1


/**********************************************************************/
//default filenames and Co. regarding the data export

#define INLAND_LETTER_FILENAME		"Antonius Briefe Inland.csv"
#define AUSLAND_LETTER_FILENAME		"Antonius Briefe Ausland.csv"
#define INLAND_PARCEL_FILENAME		"Antonius Pakete Inland.csv"
#define AUSLAND_PARCEL_FILENAME		"Antonius Pakete Ausland.csv"

#define INLAND_LETTER_NUMBER_OF_COLUMNS		14
#define AUSLAND_LETTER_NUMBER_OF_COLUMNS	14
#define INLAND_PARCEL_NUMBER_OF_COLUMNS		14
#define AUSLAND_PARCEL_NUMBER_OF_COLUMNS	14


#endif // DEFAULTMEASURES_H
