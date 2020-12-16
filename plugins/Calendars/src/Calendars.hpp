/*
 * Copyright (C) 2020 Georg Zotti
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */

#ifndef CALENDARS_HPP
#define CALENDARS_HPP

#include <QFont>
#include <QMap>
//#include <QGraphicsTextItem>

#include "StelModule.hpp"


#include "Calendar.hpp"
#include "CalendarsInfoPanel.hpp"
#include "JulianCalendar.hpp"
#include "GregorianCalendar.hpp"

class CalendarsDialog;
class StelButton;

//! Calendars plugin provides an interface to various calendars
class Calendars : public StelModule
{
	Q_OBJECT
	Q_PROPERTY(bool enabled		      READ isEnabled                WRITE enable            NOTIFY enabledChanged)
	Q_PROPERTY(bool flagShowJulian        READ isJulianDisplayed        WRITE showJulian        NOTIFY showJulianChanged)
	Q_PROPERTY(bool flagShowGregorian     READ isGregorianDisplayed     WRITE showGregorian     NOTIFY showGregorianChanged)
	Q_PROPERTY(bool flagShowISO           READ isISODisplayed           WRITE showISO           NOTIFY showISOChanged)
	Q_PROPERTY(bool flagShowChinese       READ isChineseDisplayed       WRITE showChinese       NOTIFY showChineseChanged)
	Q_PROPERTY(bool flagShowMayaLongCount READ isMayaLongCountDisplayed WRITE showMayaLongCount NOTIFY showMayaLongCountChanged)
	Q_PROPERTY(bool flagShowMayaHaab      READ isMayaHaabDisplayed      WRITE showMayaHaab      NOTIFY showMayaHaabChanged)
	Q_PROPERTY(bool flagShowMayaTzolkin   READ isMayaTzolkinDisplayed   WRITE showMayaTzolkin   NOTIFY showMayaTzolkinChanged)
	Q_PROPERTY(bool flagShowAztecXihuitl  READ isAztecXihuitlDisplayed  WRITE showAztecXihuitl  NOTIFY showAztecXihuitlChanged)
	Q_PROPERTY(bool flagShowAztecTonalpohualli READ isAztecTonalpohualliDisplayed WRITE showAztecTonalpohualli NOTIFY showAztecTonalpohualliChanged)

public:
	Calendars();
	virtual ~Calendars() Q_DECL_OVERRIDE;

	///////////////////////////////////////////////////////////////////////////
	// Methods defined in the StelModule class
	virtual void init() Q_DECL_OVERRIDE;
	//! Set all calendars to the Core's JD.
	virtual void update(double) Q_DECL_OVERRIDE;
	//! if enabled, provide a table of calendars on screen.
	virtual void draw(StelCore* core) Q_DECL_OVERRIDE;
	virtual double getCallOrder(StelModuleActionName actionName) const Q_DECL_OVERRIDE;
	virtual bool configureGui(bool show=true) Q_DECL_OVERRIDE;

	//! Restore the plug-in's settings to the default state.
	//! Replace the plug-in's settings in Stellarium's configuration file
	//! with the default values and re-load them.
	//! Uses internally loadSettings().
	void restoreDefaultSettings();

	//! Load the plug-in's settings from the configuration file.
	//! Settings are kept in the "Calendars" section in Stellarium's
	//! configuration file. If no such section exists, it will load default
	//! values.
	//! @see restoreDefaultSettings()
	void loadSettings();

	//! Get a pointer to the respective Calendar. Returns Q_NULLPTR if not found.
	//! Valid names: Julian, Gregorian
	//! TODO: ADD HERE: ISO, Chinese, MayaLC, MayaHaab, MayaTzolkin, ...
	Calendar* getCal(QString name);

signals:
	//void jdChanged(double jd);

	void enabledChanged(bool b);
	void showJulianChanged(bool b);
	void showGregorianChanged(bool b);
	void showISOChanged(bool b);
	void showChineseChanged(bool b);
	void showMayaLongCountChanged(bool b);
	void showMayaHaabChanged(bool b);
	void showMayaTzolkinChanged(bool b);
	void showAztecXihuitlChanged(bool b);
	void showAztecTonalpohualliChanged(bool b);

public slots:
	// Setters/getters
	//! is display of calendars overlay active?
	bool isEnabled() const;
	//! enable display of calendars overlay
	void enable(bool b);
	bool isJulianDisplayed() const;		//!< display Julian Calendar?
	void showJulian(bool b);		//!< activate display of Julian Calendar
	bool isGregorianDisplayed() const;	//!< display Gregorian Calendar?
	void showGregorian(bool b);		//!< activate display of Gregorian Calendar
	bool isISODisplayed() const;		//!< display ISO Calendar?
	void showISO(bool b);			//!< activate display of ISO Calendar
	bool isChineseDisplayed() const;	//!< display Chinese Calendar?
	void showChinese(bool b);		//!< activate display of Chinese Calendar
	bool isMayaLongCountDisplayed() const;	//!< display Maya Long Count?
	void showMayaLongCount(bool b);		//!< activate display of Maya Long Count
	bool isMayaHaabDisplayed() const;	//!< display Maya Haab?
	void showMayaHaab(bool b);		//!< activate display of Maya Haab
	bool isMayaTzolkinDisplayed() const;	//!< display Maya Tzolkin?
	void showMayaTzolkin(bool b);		//!< activate display of Maya Tzolkin
	bool isAztecXihuitlDisplayed() const;	//!< display Aztec Xihuitl?
	void showAztecXihuitl(bool b);		//!< activate display of Aztec Xihuitl
	bool isAztecTonalpohualliDisplayed() const; //!< display Aztec Tonalpohualli?
	void showAztecTonalpohualli(bool b);	//!< activate display of Aztec Tonalpohualli

private:
	// Font used for displaying text
	QFont font;
	CalendarsInfoPanel *infoPanel;
	CalendarsDialog* configDialog;
	StelButton* toolbarButton;
	QSettings* conf;

	// a QMap of pointers to calendars. The Names are identical to the respective Calendar subclass names, minus "Calendar".
	QMap<QString, Calendar*> calendars;

	// This is used to buffer JD for all known subcalendars.
	// Maybe we don't need it in the end...
	//double JD;

	// StelProperties:
	bool enabled;
	bool flagShowJulian;
	bool flagShowGregorian;
	bool flagShowISO;
	bool flagShowChinese;
	bool flagShowMayaLongCount;
	bool flagShowMayaHaab;
	bool flagShowMayaTzolkin;
	bool flagShowAztecXihuitl;
	bool flagShowAztecTonalpohualli;
};


#include <QObject>
#include "StelPluginInterface.hpp"

//! This class is used by Qt to manage a plug-in interface
class CalendarsStelPluginInterface : public QObject, public StelPluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID StelPluginInterface_iid)
	Q_INTERFACES(StelPluginInterface)
public:
	virtual StelModule* getStelModule() const Q_DECL_OVERRIDE;
	virtual StelPluginInfo getPluginInfo() const Q_DECL_OVERRIDE;
	virtual QObjectList getExtensionList() const Q_DECL_OVERRIDE { return QObjectList(); }
};

#endif /* CALENDARS_HPP */
