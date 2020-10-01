/**
 * @brief Admin_Statistics main scripts
 * @details Plugin / Module Scripts
 * @author CaMykS Team
 * @version 1.0.1
 * @date Creation: May 2007
 * @date Modification: Sep 2020
 * @copyright 2007 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * reload page with new date settings
 * @param int day
 * @param int month
 * @param int year
 * @return void
 * @access private
 */
function admin_statistics_showDayDetail( day, month, year ) {
  f = eval('document.'+admin_statistics_form);

  for( i=0; i< f.displaymode.length; i++ ) {
    if ( f.displaymode[i] && f.displaymode[i].value==6 )
      f.displaymode[i].checked="checked";
  }

  f.displayday_day.value = day;
  f.displayday_month.value = month;
  f.displayday_year.value = year;

  /* update form action value */
  f.action += '&openTab=detail';
  f.submit();
}

/*
 * reload page with new date settings
 * @param int month
 * @param int year
 * @return void
 * @access private
 */
function admin_statistics_showMonthDetail( month, year ) {
  f = eval('document.'+admin_statistics_form);

  for( i=0; i< f.displaymode.length; i++ ) {
    if ( f.displaymode[i] && f.displaymode[i].value==7 )
      f.displaymode[i].checked="checked";
  }

  f.displayfrom_day.value = 1;
  f.displayfrom_month.value = month;
  f.displayfrom_year.value = year;

  nd = new Date();
  nd.setFullYear( year, month, 1 );
  nd.setDate ( nd.getDate()-1 );

  f.displayto_day.value = nd.getDate();
  f.displayto_month.value = nd.getMonth()+1;
  f.displayto_year.value = nd.getFullYear();

  /* update form action value */
  f.action += '&openTab=detail';
  f.submit();
}

/*
 * reload page with new date settings
 * @param int year
 * @return void
 * @access private
 */
function admin_statistics_showYearDetail ( year ) {
  f = eval('document.'+admin_statistics_form);

  for( i=0; i< f.displaymode.length; i++ ) {
    if ( f.displaymode[i] && f.displaymode[i].value==7 )
      f.displaymode[i].checked="checked";
  }

  f.displayfrom_day.value = 1;
  f.displayfrom_month.value = 1;
  f.displayfrom_year.value = year;

  f.displayto_day.value = 31;
  f.displayto_month.value = 12;
  f.displayto_year.value = year;


  f.action += '&openTab=detail';
  f.submit();
}
