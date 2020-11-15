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

#include "StelTranslator.hpp"
#include "MayaTzolkinCalendar.hpp"
#include "MayaLongCountCalendar.hpp"
#include "StelUtils.hpp"

const int MayaTzolkinCalendar::mayanTzolkinEpoch=MayaLongCountCalendar::mayanEpoch-MayaTzolkinCalendar::mayanTzolkinOrdinal(4,20);

MayaTzolkinCalendar::MayaTzolkinCalendar(double jd): Calendar(jd)
{
	retranslate();
}

QMap<int, QString> MayaTzolkinCalendar::tzolkinNames;

void MayaTzolkinCalendar::retranslate()
{
	// fill the name lists with translated/transcribed day names
	tzolkinNames={
		{ 1, qc_("Imix"    , "Maya Tzolkin name")},
		{ 2, qc_("Ik"      , "Maya Tzolkin name")},
		{ 3, qc_("Akbal"   , "Maya Tzolkin name")},
		{ 4, qc_("Kan"     , "Maya Tzolkin name")},
		{ 5, qc_("Chicchan", "Maya Tzolkin name")},
		{ 6, qc_("Cimi"    , "Maya Tzolkin name")},
		{ 7, qc_("Manik"   , "Maya Tzolkin name")},
		{ 8, qc_("Lamat"   , "Maya Tzolkin name")},
		{ 9, qc_("Muluc"   , "Maya Tzolkin name")},
		{10, qc_("Oc"      , "Maya Tzolkin name")},
		{11, qc_("Chuen"   , "Maya Tzolkin name")},
		{12, qc_("Eb"      , "Maya Tzolkin name")},
		{13, qc_("Ben"     , "Maya Tzolkin name")},
		{14, qc_("Ix"      , "Maya Tzolkin name")},
		{15, qc_("Men"     , "Maya Tzolkin name")},
		{16, qc_("Cib"     , "Maya Tzolkin name")},
		{17, qc_("Caban"   , "Maya Tzolkin name")},
		{18, qc_("Eznab"   , "Maya Tzolkin name")},
		{19, qc_("Cauac"   , "Maya Tzolkin name")},
		{20, qc_("Ahau"    , "Maya Tzolkin name")}};
}

// Set a calendar date from the Julian day number
void MayaTzolkinCalendar::setJD(double JD)
{
	this->JD=JD;

	const int rd=fixedFromJD(JD);
	const int count=rd-mayanTzolkinEpoch+1;
	const int number = StelUtils::amod(count, 13);
	const int name = StelUtils::amod(count, 20);

	parts.clear();
	parts << number << name;

	emit partsChanged(parts);
}

// get a stringlist of calendar date elements sorted from the largest to the smallest.
// baktun-katun-tun-uinal-kin
QStringList MayaTzolkinCalendar::getDateStrings()
{
	QStringList list;
	list << QString::number(std::lround(parts.at(0)));
	list << tzolkinNames.value(std::lround(parts.at(1)));

	return list;
}


// get a formatted complete string for a date
QString MayaTzolkinCalendar::getFormattedDateString()
{
	QStringList str=getDateStrings();
	return QString("%1 %2")
			.arg(str.at(0))
			.arg(str.at(1));
}

// set date from a vector of calendar date elements sorted from the largest to the smallest.
// month-day
// We face a problem as the year is not unique. We can only find the date before current JD which matches the parts.
void MayaTzolkinCalendar::setDate(QVector<int> parts)
{
	// Problem: This sets time to midnight. We need to keep and reset the fractional day.
	const double dayFraction=JD-std::floor(JD-.5);

	this->parts=parts;

	const int rdOnOrBefore=mayanTzolkinOnOrBefore(parts, fixedFromJD(JD));

	JD=jdFromFixed(rdOnOrBefore)+dayFraction;
	emit jdChanged(JD);
}

int MayaTzolkinCalendar::mayanTzolkinOnOrBefore(QVector<int> tzolkin, int rd)
{
	return rd-((rd-mayanTzolkinEpoch-mayanTzolkinOrdinal(std::lround(tzolkin.at(0)), std::lround(tzolkin.at(1))))  % 260 );
}
