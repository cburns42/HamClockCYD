#ifndef SOLARXML_H
#define SOLARXML_H

char *testDocument = R"rawliteral(
<solar>
	<solardata>
		<source url="http://www.hamqsl.com/solar.html">N0NBH</source>
		<updated> 18 Feb 2026 1412 GMT</updated>
		<solarflux>122</solarflux>
		<aindex> 11</aindex>
		<kindex> 2</kindex>
		<kindexnt>No Report</kindexnt>
		<xray>B4.3</xray>
		<sunspots>51</sunspots>
		<heliumline>120.1</heliumline>
		<protonflux>9</protonflux>
		<electonflux>2860</electonflux>
		<aurora>3</aurora>
		<normalization>1.99</normalization>
		<latdegree>65.6</latdegree>
		<solarwind>512.2</solarwind>
		<magneticfield>-2.1</magneticfield>
		<calculatedconditions>
			<band name="80m-40m" time="day">Fair</band>
			<band name="30m-20m" time="day">Good</band>
			<band name="17m-15m" time="day">Fair</band>
			<band name="12m-10m" time="day">Fair</band>
			<band name="80m-40m" time="night">Good</band>
			<band name="30m-20m" time="night">Good</band>
			<band name="17m-15m" time="night">Fair</band>
			<band name="12m-10m" time="night">Poor</band>
		</calculatedconditions>
		<calculatedvhfconditions>
			<phenomenon name="vhf-aurora" location="northern_hemi">Band Closed</phenomenon>
			<phenomenon name="E-Skip" location="europe">Band Closed</phenomenon>
			<phenomenon name="E-Skip" location="north_america">Band Closed</phenomenon>
			<phenomenon name="E-Skip" location="europe_6m">Band Closed</phenomenon>
			<phenomenon name="E-Skip" location="europe_4m">Band Closed</phenomenon>
		</calculatedvhfconditions>
		<geomagfield>QUIET</geomagfield>
		<signalnoise>S1-S2</signalnoise>
		<fof2></fof2>
		<muffactor></muffactor>
		<muf>NoRpt</muf>
	</solardata>
</solar>
)rawliteral";
#endif