//=======================================================================================================================
//  A brief introduction to the "R-RHESSys" model, which is short for rasterized RHESSys model::
//
//  The "R-RHESSys" is developed based on the Regional Hydroecological Simulation Systems (RHESSys, Tague and Band, 2004)
//  but excluded basin, hillslope and zone related hierarchical framework/structure in its predecessor. It also excluded
//  the TOP-MODEL embedded in its predecessor. It is a strictly cell-by-cell-based model and uses spatially explicit
//  routing algorithm to simulate spatial connectivity and movement of water and dissolved nutrients among simulated cells.
//  Since vegetation growth is dynamically simulated, a spin-up simulation control for vegetation growth and associated
//  carbon dynamics was added. This enables users to model vegetation and cycling of C and N in terrestrial ecosystems.
//  In addition, land surface water balance in each cell will be checked before routing water and solutes. The model codes
//  were checked/debugged and greatly simplified compared to the original RHESSys model. In author's personal view, it is
//  easier to handle than its predecessor while most subroutines are kept identical as their counterparts in its
//  predecessor.
//
//  Running R-RHESSys, a potential alternative to the RHESSys, requires the following data:
//
//  First, DEM data and DEM-derived slope, aspect, streams, roads raster data in ArcInfor ASCII format;
//  Second, meteorological data: daily minimum and maximum temperature (in Celsius degree), and precipitation (in meter);
//  Third, annual time-series atmospheric CO2 concentration (in ppm);
//  Fourth, rasterized land-cover, land use or vegetation data to predefine land cover, land use or vegetation types;
//  Fifth, rasterized soil texture class data to predefine soil types for the study region;
//  Finally, a flow table file describes the spatial connectivity of water and nutrients movement among simulated patches.

//  Besides, four default files of patch, soil, vegetation and land-use are provided. These files include parameters
//  relevant to soil, vegetation and land-use that are required to parameterize before running R-RHESSys.

//  As its predecessor, R-RHESSys is able to simulate::
//
//  (i) Land surface hydrology, including river stream flow, base flow, ET, plant transpiration, soil moisture, and etc.
//  (ii) Ecosystem dynamics: vegetation growth and productivity, cycling of carbon and nitrogen (e.g., soil autotrophic
//       and heterotrophic respiration) in terrestrial ecosystems, and etc.
//  (iii) Biogeochemical dynamics:: soil nitrification and denitrification, river nitrate, dissolved DOC and DON,
//       soil mineralization, and etc.
//
//  Note: For simulating land surface hydrology, a least of 20-year spin-up simulations are required for leaf area index
//  to reach stable state. For simulating soil and vegetation carbon, spin-up simulations more than 150 years are required.
//
//  Users are welcome to employ R-RHESSys to regions of their own interests. Examples of model forcing data can be
//  provided for reference or learning. For other questions, please contact the author::

//  Dr. Guoping Tang
//  Division of Earth and Ecosystem Sciences
//  Desert Research Institute
//  Reno, NV 89512
//  Email: gtang@dri.edu or tangg2010@gmail.com
//  Phone: 775-673-7938 (o)

//  Date created: 08-31-2011
//=======================================================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <direct.h>
#include <omp.h>

#include "chess.h"
#include "functions.h"
#include "constants.h"

using namespace std;

//=======================================================================================================================
//GLOBAL VARS TO BE DEFINED=
//=======================================================================================================================

int thread_array[17] = { 1,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32 };
//int thread_array[17] = { 1,4,8,16,24,10,12,14,16,18,20,22,24,26,28,30,32 };
int SDI_array[8] = { 1,2,3,4,5,6,7,8 };
int SDI_flag = 1, SDI = 1;

//=======================================================================================================================
// THE MAIN INTERFACE TO CONTROL MODEL SIMULATION
//================================================s=======================================================================
int	main(int main_argc, char **main_argv)
{

	char infpath[120]{};
	char file_location[120]{};
	_getcwd(file_location, 120);

	strcpy(infpath, file_location);
	strcat(infpath, "\\thread_test_lc20.txt");

	cout << infpath << endl;
	fstream OUT_INF(infpath, ios::out);


	for (int thread_inx = 0; thread_inx != 17; thread_inx++)
		//for (int thread_inx = 0; thread_inx != 1; thread_inx++)
		{

			//int thread_num = thread_array[thread_inx];
			int thread_num = thread_array[thread_inx];

			cout << "thread_num\t" << thread_num << endl;

			//===============
			// 1\YC
			//===============
			/*
			//spatial geographic information for the study region
			const int       maxr = 146, maxc = 177;

			const double    xll = 799600.000120;
			const double    yll = 2647174.387550;
			const double    cellsize = 200;
			const float     NODATA_value = -9999;

			// define the simulation year, month and day
			const int start_year = 1960, end_year = 1964, start_month = 1, end_month = 12, start_day = 1, end_day = 31;
			const int start_hour = 1, end_hour = 24;
			//int       end_day; //The end of date in February varies between normal and leap year

			// define the time period for outputting simulation results
			// out_date_range outdate={first_year, last_year, first_month, last_month, first_day, last_day, first_hour, last_hour};
			struct out_date_range out_date = { 1972, 1972, 1, 12, 1, 31, 1, 24 };

			// define the number of spin years required for vegetation and soil carbon to reach the stable state with long-term
			// climatology. Spin interval is the period of input climate data used for spin-up simulations
			const int spin_years = 0, spin_interval = 6;
			bool      spin_flag = true;

			// define the input file prefix and paths for model forcing data
			char  prefix[20] = "xf_ws";

			//define 
			int	climate_num = 1;
			int gauge_num = 1;
			int patch_num = 13513;

			*/

			//===============
			// 2\LC
			//===============
			///*
			//spatial geographic information for the study region
			const int       maxr = 807, maxc = 662;

			const double    xll = 566351.89643887;
			const double    yll = 2634989.1804154;
			const double    cellsize = 200;
			const float     NODATA_value = -9999;

			// define the simulation year, month and day
			const int start_year = 1960, end_year = 1960, start_month = 1, end_month = 1, start_day = 1, end_day = 31;
			const int start_hour = 1, end_hour = 24;
			//int       end_day; //The end of date in February varies between normal and leap year

			// define the time period for outputting simulation results
			// out_date_range outdate={first_year, last_year, first_month, last_month, first_day, last_day, first_hour, last_hour};
			struct out_date_range out_date = { 1972, 1972, 1, 12, 1, 31, 1, 24 };

			// define the number of spin years required for vegetation and soil carbon to reach the stable state with long-term
			// climatology. Spin interval is the period of input climate data used for spin-up simulations
			const int spin_years = 0, spin_interval = 6;
			bool      spin_flag = true;

			// define the input file prefix and paths for model forcing data
			char  prefix[20] = "lc";

			//define
			int	climate_num = 1;
			int gauge_num = 1;
			int patch_num = 203914;

			//*/

			//===============
			// 3\DJ
			//===============
			/*
			//spatial geographic information for the study region
			const int       maxr = 1700, maxc = 1505;

			const double    xll = 419115;
			const double    yll = 2.67181e+06;
			const double    cellsize = 200;
			const float     NODATA_value = -9999;

			// define the simulation year, month and day
			const int start_year = 2000, end_year = 2000, start_month = 1, end_month = 1, start_day = 1, end_day = 31;
			const int start_hour = 1, end_hour = 24;
			//int       end_day; //The end of date in February varies between normal and leap year

			// define the time period for outputting simulation results
			// out_date_range outdate={first_year, last_year, first_month, last_month, first_day, last_day, first_hour, last_hour};
			struct out_date_range out_date = { 2007, 2008, 1, 12, 1, 31, 1, 24 };

			// define the number of spin years required for vegetation and soil carbon to reach the stable state with long-term
			// climatology. Spin interval is the period of input climate data used for spin-up simulations
			const int spin_years = 0, spin_interval = 6;
			bool      spin_flag = true;

			//define the input file prefix and paths for model forcing data
			char  prefix[20] = "dj";

			//define
			int	climate_num = 11;
			int gauge_num = 1;
			int patch_num =790304;
		    */

			char file_prefix[120]{};
			strcpy(file_prefix, file_location);
			strcat(file_prefix, "\\");
			strcat(file_prefix, prefix);
			strcat(file_prefix, "\\");

			char  inImgFile[121] = {};
			strcpy(inImgFile, file_prefix);
			strcat(inImgFile, "geo\\");

			char  inFlowFile[121] = {};
			strcpy(inFlowFile, file_prefix);
			strcat(inFlowFile, "geo\\");

			char  inClimPath[121] = {};
			strcpy(inClimPath, file_prefix);
			strcat(inClimPath, "clim\\");

			cout << inClimPath << endl;

			char  inDefFile[121] = {};
			strcpy(inDefFile, file_prefix);
			strcat(inDefFile, "defs\\");

			char  outPutPath[121] = {};
			strcpy(outPutPath, file_prefix);
			strcat(outPutPath, "out\\");

			cout << outPutPath << endl;

			char  FlowTableName[40]{};
			strcpy(FlowTableName, prefix);
			strcat(FlowTableName, "_flow_table_D8.dat");
			cout << FlowTableName << endl;


			//=======================================================================================================================
			//xu. LOCAL VARS FOR SIMULATION
			//=======================================================================================================================

			struct  date current_date {};
			struct  output_hydro_plant DM_outfiles {};
			struct  input_Clim_Files   inClimFiles {};
			struct  reservoir_object   reservoir;
			struct command_line_object *command_line = new struct command_line_object;
			struct OutArray_object *OutArray = new struct OutArray_object;
			struct parallel_object *parallel = new struct parallel_object;


			//xu. for lower use memory we use patch_num instead of cols*rows
			//only 1/4 memory are needed now
			struct patch_object *patch = new struct patch_object[patch_num]{};
			struct  daily_clim_object *daily_clim = new struct daily_clim_object[climate_num]{};//change it as a pointer

			int		*gauge_list = new int [GAUGE_NUM] {};

			int     kk = 0;
			int     f_flag = 1, arc_flag = 1, CO2_flag = 1, out_flag = 0;
			int     i = 0, j = 0, endyear = 0, spin_yrs = 0;
			int     firstmonth, lastmonth, firstday, lastday;
			clock_t  t, t1, t2, t3;
			double   land_time{}, channel_time{};

			//=======================================================================================================================
			//xu. BUILD AND INITIAL THE ENDVIRONMENT FOR SIMULATION
			//=======================================================================================================================
			//printf("Starting initialization:: \n");

			//construct and assign command line arguments
			construct_command_line(main_argc, main_argv, command_line);

			//xu. I sugguest should 1\ flow table then  2\construct patch and read images
			parallel->patch_num = construct_routing_topology(patch, inFlowFile, FlowTableName, maxr, maxc);
			parallel->cell_size = cellsize;
			parallel->thread_num = thread_num;

			//reading GRASS- or ArcInfo-based input images such as DEM,slope,aspect....stream,roads, gauge_lists
			read_geo_images(patch, command_line, maxr, maxc, cellsize, xll, yll, inImgFile, prefix, f_flag, arc_flag, parallel->patch_num, gauge_list, thread_num);

			//Initialize the default values of patch fields/members
			construct_patch(patch, command_line, maxr, maxc, inDefFile, prefix, parallel->patch_num);

			//open input climate files (daily precipitation, minimum temperature and maximum temperature)
			inClimFiles = open_Clim_Files(inClimPath, prefix);

			//distribute parallel threads of each
			init_parallel_environment(patch, parallel);

			//xu. 11 minute process of initialization are now shorter to 40 second

			//=======================================================================================================================
			//xu. SPIN UP and CHESS SIMULATION
			//=======================================================================================================================

			printf("\n Starting simulation:: \n");
			do {
				t1 = clock();
				if (spin_yrs < spin_years) { //&& command_line->grow_flag>0
					endyear = start_year + spin_interval - 1;
					spin_flag = true;

					//spin_up needs routing_flag now for channel flow
					command_line->routing_flag = 1;
				}
				else {
					endyear = end_year;
					spin_flag = false;
					command_line->routing_flag = 1;
				}

				//contruct daily output files
				if (!spin_flag && out_flag == 0) {

					//basin-level
					if (!spin_flag && command_line->b != NULL) {
						construct_basin_output_files(outPutPath, &DM_outfiles, command_line);
					}
					//xu. gauge-level
					if (!spin_flag && command_line->gg != NULL) {
						construct_gauge_output_files(patch, outPutPath, &DM_outfiles, command_line, gauge_list);
					}
					out_flag = 1;
				}

				//=======================================================================================================================
				//xu. STARTING CHESS SIMULATION by YEAR, MON and DAY
				//=======================================================================================================================

				channel_time = land_time = 0;

				for (current_date.year = start_year; current_date.year <= endyear; current_date.year++) {


					t1 = clock();

					if (current_date.year == start_year)
						firstmonth = start_month;
					else
						firstmonth = 1;

					if (current_date.year == end_year)
						lastmonth = end_month;
					else
						lastmonth = 12;

					init_phenology_object(patch, parallel->patch_num);

					for (current_date.month = firstmonth; current_date.month <= lastmonth; current_date.month++) {

						//construct patch-level daily output files for a month
						if (!spin_flag && command_line->p != NULL) {
							construct_patch_output_files(current_date, out_date, outPutPath, patch_num, &DM_outfiles, OutArray, command_line);
						}

						if (current_date.year == start_year && current_date.month == start_month)
							firstday = start_day;
						else
							firstday = 1;

						if (current_date.year == end_year && current_date.month == end_month)
							lastday = end_day;
						else
							lastday = end_day_norm_leap(current_date.year, current_date.month - 1);

						//determine if the year is leap year and thus the end day of February can be different
						//end_day=end_day_norm_leap(current_date.year,=current_date.month-1);


						//=======================================================================================================================
						//xu. DAILY SIMULATION (THREE KEY PROCESSES)
						//=======================================================================================================================
						for (current_date.day = firstday; current_date.day <= lastday; current_date.day++) {

							//-----------------------------------------------------------------------------------------------------------------------
							//xu. CLIMATE.. Read input climate data Precipitation, Tmin, Tmax and annual CO2
							//---------------------------------------------------------------------------------------------------------------------------
							chess_climate_daily(inClimFiles, current_date, daily_clim, climate_num, start_year, start_month, start_day, &CO2_flag);

							t1 = clock();

							land_time -= omp_get_wtime();

							//---------------------------------------------------------------------------------------------------------------------------
							//xu. PATCH.. Initial and run parallel CHESS daily Ecohydrological process and Transport of water and nutrients
							//---------------------------------------------------------------------------------------------------------------------------
							chess_patch_daily(patch, command_line, current_date, daily_clim, parallel);//daily_clim is a pointer now, the changes through out chess land daily


							t2 = clock();
							land_time += omp_get_wtime();
							channel_time -= omp_get_wtime();

							//---------------------------------------------------------------------------------------------------------------------------
							//xu. CHANNEL.. Channel flow routing process the route out the water
							//---------------------------------------------------------------------------------------------------------------------------
							chess_channel_daily(patch, command_line, current_date, parallel, daily_clim);

							t3 = clock();
							channel_time += omp_get_wtime();


							//output daily-step variables
							if (!spin_flag) {
								if (command_line->b != NULL)
									out_basin_level_daily(parallel->patch_num, patch, current_date, out_date, &DM_outfiles, command_line);
								if (command_line->p != NULL)
									out_patch_level_daily(parallel->patch_num, patch, current_date, out_date, &DM_outfiles, OutArray, command_line);
								if (command_line->gg != NULL)
									out_gauge_level_daily(parallel->patch_num, patch, current_date, out_date, &DM_outfiles, command_line, gauge_list, cellsize);
							}

						}
						//=======================================================================================================================
						//END OF DAILY SIMULATION
						//=======================================================================================================================

						

						//close patch_level_output_files
						if (!spin_flag && command_line->p == true)
							close_patch_output_files(&DM_outfiles, OutArray);

					} //end of months

					OUT_INF << prefix << "\t" << thread_num << "\t" << SDI << "\t" << current_date.year << "\t" << land_time << "\t" << channel_time << endl;

					CO2_flag = 1;

					if (!spin_flag)
						printf("year, month and day:: %d %d %d %lf %lf\n", current_date.year, current_date.month - 1, current_date.day - 1, land_time, channel_time);

					spin_yrs += 1;
					if (spin_yrs == spin_years && spin_flag) break;
				}


				//=======================================================================================================================
				//END OF YEARS
				//=======================================================================================================================

				if (spin_flag) {
					rewind_daily_clim(inClimFiles);
					//printf("Spin-up to %d years takes %f minutes \n", spin_yrs, ((float)(clock() - t) / CLOCKS_PER_SEC / 60.));
				}

			} while (spin_flag);

			if (current_date.year == end_year)
				cout << "\n\n" << land_time << "\t" << channel_time << endl;;

			if (command_line->b != NULL)
			{
				fclose(DM_outfiles.fBasinDailyHydro);
				fclose(DM_outfiles.fBasinDailyPlant);
			}


			delete[] patch;
			delete[] daily_clim;

			delete command_line;

			

			//=======================================================================================================================
			//END OF SIMULATION
			//=======================================================================================================================
		}
	return (0);
} //end of main programs
  //=======================================================================================================================