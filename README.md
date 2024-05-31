# Low-Cost-Multiparameter-Water-Quality-Sesnor

This GitHub repository provides updated designs for a low-cost, open-source, multiparameter water quality sensor. This sensor has the capability of measuring both chlorophyll a
and turbidity levels in water samples. This project is funded by the MOORE Foundation in conjunction with the SOCON (Sustained Ocean Color Observations from Nanosatellites) program. The goal of this project is to create a low-cost multiparameter sensor that can be distributed to participatory science networks to obtain a wide breadth of in situ water quality data to compare to satellite algorithms for water quality parameters. 

Please read the following for a high-level overview of the project and the contents of this repository.

# Table of contents
1. [Introduction](#introduction)
2. [How to Build the Sensor](#paragraph1)
3. [Data Analysis](#paragraph2)
4. [Future USe with Participatory Science Networks](#paragraph3)

## This is the introduction <a name="introduction"></a>

This sensor contains components from low-cost chlorophyll a sensors ("In situ measurements of phytoplankton fluorescence using low cost electronics" Leeuw et al., 2013, 
"Hardware Selection and Performance of Low-Cost Fluorometers" Hixson et al., 2022), as well as low-cost turbidity sensors ("Open-source, low-cost, in-situ turbidity sensor for river network monitoring" Droujko et al., 2022, "Increased scale and accessibility of sediment transport research in rivers through practical, open-source turbidity and depth sensors" Langhorst et al., 2023). Both chlorophyll a and turbidity components were integrated to make a singular benchtop sensor capable of measuring both chlorophyll a and 
turbidity in water samples. 

This repository contains information on the design of this sensor as well as data regarding its measurements of water samples and possible applications for future
deployment in participatory science networks. This sensor a Particle Argonr, an Adafruit Adalogger Featherwing for local data storage, an AS7341 light sensor, an AW9523 LED driver, multiple LEDs, and a water-resistant enclosure.

## How to Build the Sensor <a name="paragraph1"></a>
* Getting started with the code: [Firmware] (https://github.com/COAST-Lab/Low-Cost-Multiparameter-Water-Quality-Sesnor/tree/main/Firmware).
* Link to parts, suppliers, and costs:
* Cuvette Design: [Cuvette Design] (https://github.com/COAST-Lab/Low-Cost-Multiparameter-Water-Quality-Sesnor/tree/main/Hardware/Cuvette%20Holder)
* Water Resistant Housing: [Water Resistant Housing] (https://github.com/COAST-Lab/Low-Cost-Multiparameter-Water-Quality-Sesnor/tree/main/Hardware/Water%20Resistant%20Housing)

## Data Analysis <a name="paragraph2"></a
Both the chlorophyll a and turbidity portions of the sensor underwent tests with Rhodamine (chlorophyll a) and Formazin (turbidity) standards separately. The chlorophyll a portion of these tests contains multiple design changes of the cuvette holder as these tests were performed before turbidity was integrated into the sensor.

These tests without the water resistant housing and can be found at: 
* Chlorophyll [Rhodamine Dilution Tests] (https://github.com/COAST-Lab/Low-Cost-Multiparameter-Water-Quality-Sesnor/tree/main/Chlorophyll/Data%20Analysis/AS7341%20Dilution%20Tests)
* Turbidity [Formazin Dilution Tests] (https://github.com/COAST-Lab/Low-Cost-Multiparameter-Water-Quality-Sesnor/tree/main/Turbidity/Data%20Analysis/AS7341%20Dilution%20Tests)

Following the construction of the water resistant housing, both the chlorphyll a and turbidity portions of the sensor underwent dilution tests. The slope of these tests were used to calibrate the sensor for field testing. 

These tests with the water resistant housing can be found at:
* Chlorophyll [Rhodamine Dilution Test with Water Resistant Housing] (https://github.com/COAST-Lab/Low-Cost-Multiparameter-Water-Quality-Sesnor/tree/main/Chlorophyll/Data%20Analysis/Dilution%20Tests%20with%20Water%20Resistant%20Housing)
* Turbidity [Formazin Dilution Test with Water Resistant Housing] (https://github.com/COAST-Lab/Low-Cost-Multiparameter-Water-Quality-Sesnor/tree/main/Turbidity/Data%20Analysis/Dilution%20Tests%20with%20Water%20Resistant%20Housing)

Following this field tests were performed on the multiparameter low-cost sensor. Field test results/data analysis can be found at:
[Field Tests] (https://github.com/COAST-Lab/Low-Cost-Multiparameter-Water-Quality-Sesnor/tree/main/Field%20Tests)


## Future Use with Participatory Science Networks <a name="paragraph3"></a>
The goal of this project is to create a low-cost multiparameter sensor that can be distributed to participatory science networks to obtain a wide breadth of in situ water quality data to compare to satellite algorithms for water quality parameters. Currently, this sensor is not comparable to commercial sensors so this is not possible. However, information has been provided in the form of a handout to participatory science networks when this does occur. 
